#include "first_pass.h"

int DC = 0;
int IC = 0;
struct symbol_value {
    int type; /* 0: data, 1: opcode */
    int count; /* DC for data, IC for opcode */
};

void first_pass(char *am_file_name, hash_table symbols, hash_table macros) {
    char line[MAX_LINE] = {0}, word_buffer[MAX_LINE] = {0}, symbol_name[MAX_SYMBOL_LENGTH] = {0};
    int error = 0, symbol_flag = 0, offset = 0, total_offset = 0, line_index = -1;
    FILE *am_file = fopen_with_ending(am_file_name, ".am", "r");


    while (fgets(line, MAX_LINE, am_file)) {
        printf("\n");
        line_index++;
        printf("inside line %d: %s", line_index, line);
        /* new initials for each line */
        symbol_name[0] = '\0';
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
                sscanf(line + total_offset, "%[^\n]", word_buffer); /* this way im deleting leading white-spaces */
                handle_data(word_buffer, &error);
            } else {
                sscanf(line + total_offset, "%s", word_buffer);
                handle_string(word_buffer, &error);
            }

            if (error) {
                print_error(error, line_index);
            }
            continue;
        }

        if (!strcmp(word_buffer, ".extern") || !strcmp(word_buffer, ".entry")) {
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
            handle_opcode(word_buffer, &error);
            if (error) {
                print_error(error, line_index);
            }
            continue;
        }

        /* if got here no save word represent the first word of the line, need to exit */
        print_error(5, line_index);
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
    if (!check_comma(arg)) {
        *error = 3; /* 3: error in .data line arguments */
        return;
    }

    /* arguments of .data are valid, need to code them into memory */
    strcpy(copy, arg);
    token = strtok(copy, ",");

    while (token != NULL) {
        /* Process token here */

        token = strtok(NULL, ",");
    }
}


/* 6, -9,, */
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


/* HANDALING .STRING LINE */
void handle_string(char *str, int *error) {
    char copy[MAX_LINE] = {0}, *token = NULL;
    if (!check_string(str)) {
        *error = 4; /* 4: error in .string string */
        return;
    }

    /* if got here string is valid, need to code each char into memory */
    strcpy(copy, str);
    token = strtok(copy, ",");

    while (token != NULL) {
        /* Process token here */

        token = strtok(NULL, ",");
    }
}


int check_string(char *str) {
    size_t length = strlen(str);
    size_t i;

    /* Check if the string is at least 2 characters long */
    if (length < 2) {
        printf("string '%s' is too short", str);
        return 0;
    }  /* Too short to have leading and trailing quotes */

    /* Check leading and trailing quotation marks */
    if (str[0] != '"' || str[length - 1] != '"') {
        printf("%s does not have open/close quotation mark\n", substring(str, 0, length-1));
        return 0;
    }

    /* Check if every character in between is printable */
    for (i = 1; i < length - 1; i++) {
        if (!isprint((unsigned char)str[i])) {
            printf("the char '%c' inside the string '%s' is not printable by the isprint() func", str[i], str);
            return 0;
        }
    }

    return 1;  /* String is valid */
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
    if (!strcmp(word, "mov") || !strcmp(word, "cmp") || !strcmp(word, "add") || !strcmp(word, "sub") || !strcmp(word, "lea") || !strcmp(word, "clr") || !strcmp(word, "not") || !strcmp(word, "inc") || !strcmp(word, "dec") || !strcmp(word, "jmp") || !strcmp(word, "bne") || !strcmp(word, "red") || !strcmp(word, "prn") || !strcmp(word, "jsr") || !strcmp(word, "rts") || !strcmp(word, "stop"))
        return 1;
    return 0;
}

void handle_opcode(char *word, int *error) {
    printf("in handle_opcode() function\n");
}

