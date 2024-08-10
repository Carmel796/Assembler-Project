#include "first_pass.h"

int DC = 0;
int IC = 0;
short data_image[4096] = {0};
short code_image[4096] = {0};




struct instruction opcode_array[] = {
    {"mov", 2, {1, 1, 1, 1}, {0, 1, 1, 1}},
    {"cmp", 2, {1, 1, 1, 1}, {1, 1, 1, 1}},
    {"add", 2, {1, 1, 1, 1}, {0, 1, 1, 1}},
    {"sub", 2, {1, 1, 1, 1}, {0, 1, 1, 1}},
    {"lea", 2, {0, 1, 0, 0}, {0, 1, 1, 1}},
    {"clr", 1, {0, 0, 0, 0}, {0, 1, 1, 1}},
    {"not", 1, {0, 0, 0, 0}, {0, 1, 1, 1}},
    {"inc", 1, {0, 0, 0, 0}, {0, 1, 1, 1}},
    {"dec", 1, {0, 0, 0, 0}, {0, 1, 1, 1}},
    {"jmp", 1, {0, 0, 0, 0}, {0, 1, 1, 0}},
    {"bne", 1, {0, 0, 0, 0}, {0, 1, 1, 0}},
    {"red", 1, {0, 0, 0, 0}, {0, 1, 1, 1}},
    {"prn", 1, {0, 0, 0, 0}, {1, 1, 1, 1}},
    {"jsr", 1, {0, 0, 0, 0}, {0, 1, 1, 0}},
    {"rts", 0, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {"stop", 0, {0, 0, 0, 0}, {0, 0, 0, 0}}
};


void first_pass(char *am_file_name, hash_table symbols, hash_table macros) {
    char line[MAX_LINE] = {0}, word_buffer[MAX_LINE] = {0}, symbol_name[MAX_SYMBOL_LENGTH] = {0}, opcode_temp[MAX_LINE] = {0};
    int error = 0, symbol_flag = 0, offset = 0, total_offset = 0, line_index = -1, i;
    FILE *am_file = fopen_with_ending(am_file_name, ".am", "r");


    while (fgets(line, MAX_LINE, am_file)) {
        printf("\n");
        line_index++;
        printf("inside line %d: %s", line_index, line);

        /* new initials for each line */
        symbol_name[0] = '\0';
        word_buffer[0] = '\0';
        opcode_temp[0] = '\0';
        symbol_flag = 0;
        offset = 0;
        total_offset = 0;
        error = 0;

        /* gets first word of line into first_word, and first_word length into offset */
        if (!sscanf(line, "%s%n", word_buffer, &offset))
            continue;


        total_offset += offset;

        printf("first word of line %d: %s\n", line_index, word_buffer);

        /* if label detected, and no error occur, symbol flag updating to True, symbol-name updating, and the "first_word" is now the second */
        if (is_label(word_buffer, &error, macros, symbols)) {
            if (error) {
                print_error(error, line_index);
                continue;
            }

            symbol_flag = 1;
            strcpy(symbol_name, word_buffer);
            sscanf(line + total_offset, "%s%n", word_buffer, &offset);
            total_offset += offset;
        }

        if (!strcmp(word_buffer, ".data") || !strcmp(word_buffer, ".string")) {
            if (symbol_flag) {
                printf("adding symbol: %s to symbol table\n", symbol_name);
                add_symbol(symbols, symbol_name, DC, 0);
            }

            /* distinguish between .data and .string, any errors will add to error variable */
            if (!strcmp(word_buffer, ".data")) {
                sscanf(line + total_offset, "%[^\n]", word_buffer); /* now word_buffer contain the arguments of .data */
                handle_data(word_buffer, &error);
            } else {
                sscanf(line + total_offset, "%[^\n]", word_buffer);
                handle_string(word_buffer, &error);
            }

            if (error) {
                print_error(error, line_index);
            }
            continue;
        }

        if (!strcmp(word_buffer, ".extern") || !strcmp(word_buffer, ".entry")) {
            if (symbol_flag) {
                print_error(10, line_index);
            }
            /* distinguish between .data and .string, any errors will add to error variable */
            if (!strcmp(word_buffer, ".extern")) {
                handle_extern(line + offset, &error);
            } else {
                handle_entry(line + offset, &error);
            }

            if (error) {
                print_error(error, line_index);
            }
            continue;
        }

        if (is_opcode(word_buffer)) {
            if (symbol_flag) {
                printf("adding symbol: %s to symbol table\n", symbol_name);
                add_symbol(symbols, symbol_name, IC, 1);
            }
            strcpy(opcode_temp, word_buffer);
            sscanf(line + total_offset, "%[^\n]", word_buffer);
            handle_opcode(opcode_temp, word_buffer, &error, symbols);
            if (error) {
                print_error(error, line_index);
            }
            continue;
        }

        /* if got here no save word represent the first word of the line, need to exit */
        print_error(5, line_index);
    }

    printf("Printing Data-Image:\n");
    for (i = 0; i < DC; i++) {
        printf("array[%d] = ", i);
        print_binary(data_image[i]);
    }

    printf("Printing Code-Image:\n");
    for (i = 0; i < IC; i++) {
        printf("array[%d] = ", i);
        print_binary(code_image[i]);
    }
    fclose(am_file);
}

/* HANDALING SYMBOL IN LINE */
int is_label(char *name, int *error, hash_table macros, hash_table symbols) {
    int len = strlen(name);

    /* does is even a symbol definition? */
    if (name[len-1] != ':') {
        return 0; /* not a symbol definition */
    }

    /* if here, detected an ':', now need to check if the symbol name is OK */
    if (!check_symbol_name(name)) {
        *error = 1; /* 1: error in label name */
        return 1; /* symbol, but error detected in symbol-name */
    }

    /* if got here, there is symbol definition and the symbol name is OK, need to check in macros & symbols table if already defined */
    if (search(macros, name) || search(symbols, name)) {
        *error = 2; /* 2: existing macro / symbol with the same name */
        return 1; /* symbol, but already exist in macro / symbol table */
    }

    /* if got here, there is a symbol, with correct name, and no exiting macro / symbol with the same name */
    return 1;
}

int check_symbol_name(char *name) {
    int len = strlen(name);
    char *sub = NULL;

    /* checl the requirments of label name */
    if (len > 31 || !isalpha(name[0]) || !alpha_and_numeric_only_string((sub = substring(name, 1, len-1)))){
        free(sub);
        return 0;
    }

    /* label name is fine and meets the requirments of label name */
    free(sub);
    return 1;
}

void add_symbol(hash_table symbols, char *key, int count, int flag) {
    node symbol;
    struct symbol_value *value = safe_malloc(sizeof(struct symbol_value));
    value->type = flag;
    value->count = count;

    symbol = create_node(key, value);
    insert(symbols, symbol);
}


/* HANDALING .DATA LINE */
void handle_data(char *arg, int *error) {
    char copy[MAX_LINE] = {0}, *token = NULL;
    short bin_num = 0;
    int number;
    if (!check_comma(arg)) {
        *error = 3; /* 3: error in .data line arguments */
        return;
    }

    /* arguments of .data are valid, need to code them into memory */
    strcpy(copy, arg);
    token = strtok(copy, COMMA_DELIM);

    while (token != NULL) {
        /* Process token here */
        if (!check_data_num(token)) {
            *error = 9;
            break;
        }

        number = strtol(token, NULL, 10);
        int_to_binary(number, &bin_num);
        data_image[DC] = bin_num;
        DC++;
        token = strtok(NULL, COMMA_DELIM);
    }
}

int check_data_num(char *num) {
    /* Define a buffer to hold the copied string, with space for null terminator */
    char copy[83], *start = NULL, *end = NULL;

    /* Copy the original string to the buffer */
    strcpy(copy, num);
    start = copy;

    /* Skip leading whitespace */
    while (isspace((unsigned char)*start)) {
        start++;
    }

    /* If after skipping whitespaces the string is empty */
    if (*start == '\0') {
        return 0;  /* Invalid number */
    }

    /* Find the end of the string */
    end = start + strlen(start) - 1;

    /* Skip trailing whitespace */
    while (end > start && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }

    /* Check if the string starts with a '+' or '-' sign */
    if (*start == '+' || *start == '-') {
        start++;  /* Move to the next character */
    }

    /* Check if the string is now empty after a sign */
    if (*start == '\0') {
        return 0;  /* Invalid number (just a sign with no digits) */
    }

    /* Traverse the rest of the string and ensure all characters are digits */
    while (*start != '\0') {
        if (!isdigit((unsigned char)*start)) {
            return 0;  /* Invalid character found */
        }
        start++;
    }

    return 1;  /* The string is a valid number */
}


/* HANDALING .STRING LINE */
void handle_string(char *str, int *error) {
    char copy[MAX_LINE] = {0};
    int start = 0, end = 0;
    if (!check_string(str, &start, &end)) {
        *error = 4; /* 4: error in .string string */
        return;
    }

    /* if got here string is valid, need to code each char into memory */
    strcpy(copy, str);

    for (;start <= end; start++) {
        data_image[DC] = copy[start];
        DC++;
    }

    /* Indication of string end */
    data_image[DC] = '\0';
    DC++;
}

/* s_index: start index, e_index: end index */

int check_string(char *str, int *s_index, int *e_index) {
    /* Define a buffer to hold the copied string, with space for null terminator AND Pointers to traverse the copied string */
    char copy[83], *p, *start, *end;

    /* Copy the original string to the buffer */
    strcpy(copy, str);

    /* Initialize pointers */
    start = copy;
    end = copy + strlen(copy) - 1;

    /* Skip leading whitespace */
    while (isspace((unsigned char)*start)) {
        start++;
    }

    /* If the string is too short to have quotes or is empty */
    if (*start == '\0' || strlen(start) < 2) {
        return 0;  /* Invalid string */
    }

    /* Skip trailing whitespace */
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }

    /* Check if the string starts and ends with double quotes */
    if (*start != '\"' || *end != '\"') {
        return 0;  /* Invalid string */
    }

    /* Store the start and end indices (excluding the quotes) */
    *s_index = (start - copy) + 1;  /* Index of the first character inside the quotes */
    *e_index = (end - copy) - 1;    /* Index of the last character inside the quotes */

    /* Traverse the characters between the quotes */
    for (p = start + 1; p < end; p++) {
        if (!isprint((unsigned char)*p)) {
            return 0;  /* Invalid character found */
        }
    }

    return 1;  /* The string is valid */
}

/* HANDALING .EXTERN LINE */
void handle_extern(char *word, int *error) {
    printf("in handle_extern() function\n");
}


/* HANDALING .ENTRY LINE */
void handle_entry(char *word, int *error) {
    printf("in handle_entry() function\n");
}


/* HANDALING OPCODE LINE */
int is_opcode(char *word) {
    printf("checking if: %s, an opcode\n", word);
    return linear_search(opcode_array, OPCODE_ARRAY_SIZE, word) != -1 ? 1 : 0;
}

void handle_opcode(char *opcode, char *arg, int *error, hash_table symbols) {
    short inst_word = 0;
    int index = linear_search(opcode_array, OPCODE_ARRAY_SIZE, opcode), token_count = 0, curr_addressing_method = 0, ic_holder = IC, source_or_dest = 0;
    char copy[MAX_LINE], *token = NULL;


    if (!check_comma(arg)) {
        *error = 12;
        return;
    }

    strcpy(copy, arg);
    printf("in handle_opcode() function\n");
    if (index != -1) {
        inst_word = index << 11;
    } else {
        *error = 11;
        return;
    }

    token = strtok(copy, COMMA_DELIM);
    while (token != NULL) {
        /* initialization */
        token_count++;
        IC++; /* word of operand is about to be written, increasing IC from the first operand for saving ic_holder for the inst_word */
        curr_addressing_method = check_operand(token);

        if (curr_addressing_method == -1) {
            *error = 14;
            return;
        }

        if (token_count == 1) {
            if (!is_all_zeros(opcode_array[index].legal_src, 4)) { /* this token should refer as a source operand token */
                if (!check_opcode_operand_type(source_or_dest, index, curr_addressing_method, error)) return;
                set_bit_to_one(&inst_word, curr_addressing_method + 7);
            } else { /* there is only one token and it is the dest token */
                source_or_dest = 1;
                if (!check_opcode_operand_type(source_or_dest, index, curr_addressing_method, error)) return;
                set_bit_to_one(&inst_word, curr_addressing_method + 3);

            }
        } else { /* this is the second operand, for sure its the dest */
            source_or_dest = 1;
            if (!check_opcode_operand_type(source_or_dest, index, curr_addressing_method, error)) return;
            set_bit_to_one(&inst_word, curr_addressing_method + 3);

        }

        if (token_count > get_arg_count(index)) {
            *error = 13;
            return;
        }
        printf("argument %d for opcode %s is: %s\n", token_count, opcode, token);

        /* insert into word in bits 10-7 source operand addressing, in 6-3 target operand addressing, in 2-0 the 'A', 'R', 'E' */
        if (curr_addressing_method == 0) { /* curr_addressing_method == 0 means its a number */
            code_image[IC] = get_number_from_operand(token) << 3;
            set_bit_to_one(&code_image[IC], 2);
        }
        else if (curr_addressing_method == 1) {
            code_image[IC] = 0; /* probably a label that defined later in code */
        }
        else { /* curr_addressing_method == 2 or 3 means its a register */
            if (source_or_dest) {
                code_image[IC] = get_number_from_operand(token) << 6;
            } else {
                code_image[IC] = get_number_from_operand(token) << 3;
            }
            set_bit_to_one(&code_image[IC], 2);
        }

        print_binary(code_image[IC]);

        token = strtok(NULL, COMMA_DELIM);
    }
    if (token_count != get_arg_count(index)) {
        *error = 13;
        return;
    }
    set_bit_to_one(&inst_word, 2); /* 'ARE' of instruction line is alwats A */
    code_image[ic_holder] = inst_word;
    print_binary(inst_word);

    IC++; /* if IC not increased here, next line will overwrite the last operand word of this line */
}


void set_bit_to_one(short *src, int index) {
    *src = *src | 1 << index;
}

int check_operand(char *token) {
    char copy[MAX_LINE];
    int i = 0;
    strcpy(copy, token);

    while (isspace(copy[i])) i++;

    if (copy[i] == '#') {
        return check_data_num(token + i + 1) ? 0 : -1;
    }
    if (copy[i] == '*') {
        return check_register_name(token + i + 1) ? 2 : -1;
    }
    if (copy[i] == 'r') {
        return check_register_name(token + i) ? 3 : -1;
    }
    return 1; /* SHOULD I CHECK THAT IF OPERNAD IS SYMBOL - THAT THE SYMBOL NAME MEET THE REQUIRMENTS? */
}

int check_register_name(char *name) {
    char copy[MAX_LINE];
    int i = 0;
    strcpy(copy, name);

    if (copy[i] != 'r') return 0;
    i++;
    if (copy[i] != '0' && copy[i] != '1' && copy[i] != '2' && copy[i] != '3' && copy[i] != '4' && copy[i] != '5' && copy[i] != '6' && copy[i] != '7') return 0;
    i++;
    while (copy[i] != '\0') {
        if (!isspace(copy[i])) return 0;
    }

    return 1;
}

int get_number_from_operand(char *token) {
    char *copy = token;
    strcpy(copy, token);

    while (*copy != '#' && *copy != 'r') copy++;
    return atoi(copy+1);
}

int check_opcode_operand_type(int dest_flag, int index, int addressing_method, int *error) {
    if ((!dest_flag && opcode_array[index].legal_src[addressing_method] == 0) || (dest_flag && opcode_array[index].legal_dst[addressing_method] == 0)) { /* the operand type does not match the opcode allowed types */
        *error = 15;
        return 0;
    }

    return 1;
}


/* MULTIPLE-USE FUNCTIONS */
bool check_comma(const char *arg) {
    bool expect_comma = false;
    while (*arg != '\0') {
        if (isspace(*arg)) {
            arg++;
        } else if (*arg == ',') {
            if (empty_line((char *)arg+1) | !expect_comma) return false;
            expect_comma = false;
            arg++;
        } else {
            if (expect_comma) return false;
            while (*arg != ',' && !isspace(*arg) && *arg != '\0') {
                arg++;
            }
            expect_comma = true;
        }
    }
    return true;
}

int get_arg_count(int opcode_index) {
    return opcode_array[opcode_index].arg_count;
}

