#include "first_pass.h"


struct symbol_value {
    int type; /* 0: data, 1: opcode */
    int count; /* DC for data, IC for opcode */
};

void first_pass(char *am_file_name, hash_table symbols, hash_table macros) {
    char line[MAX_LINE], word_buffer[MAX_LINE], symbol_name[MAX_SYMBOL_LENGTH];
    int error = 0, error_size = 0, symbol_flag = 0, offset, total_offset, line_index = -1;
    FILE *am_file = fopen_with_ending(am_file_name, ".am", "r");

    DC = 0;
    IC = 0;

    while (fgets(line, MAX_LINE, am_file)) {
        printf("\n");
        line_index++;
        printf("inside line %d: %s", line_index, line);
        /* new initials for each line */
        symbol_name[0] = '\0';
        symbol_flag = 0;
        offset = 0;
        total_offset = 0;

        /* gets first word of line into first_word, and first_word length into offset */
        sscanf(line, "%s%n", word_buffer, &offset);
        total_offset += offset;

        printf("first word of line %d: %s\n", line_index, word_buffer);

        /* if label detected, and no error occur, symbol flag updating to True, symbol-name updating, and the "first_word" is now the second */
        if (is_label(word_buffer, &error, macros, symbols)) {
            if (error) {
                print_error(error);
                break;
            }

            symbol_flag = 1;
            strcpy(symbol_name, word_buffer);
            sscanf(line + total_offset, "%s%n", word_buffer, &offset);
            total_offset += offset;

        }

        if (!strcmp(word_buffer, ".data") || !strcmp(word_buffer, ".string")) {
            if (symbol_flag) {
                printf("symbol detected for line %d: '%s\n'", line_index, symbol_name);
                add_symbol(symbols, word_buffer, DC, 0);
            }

            /* distinguish between .data and .string, any errors will add to error variable */
            if (!strcmp(word_buffer, ".data")) {
                sscanf(line + total_offset, "%s", word_buffer); /* this way im deleting leading white-spaces */
                handle_data(word_buffer, &error);
            } else {
                sscanf(line + total_offset, "%s", word_buffer);
                handle_string(word_buffer, &error);
            }

            if (error) {
                print_error(error);
                break;
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
                print_error(error);
                break;
            }
            continue;
        }

        if (is_opcode(word_buffer)) {
            handle_opcode(word_buffer, &error);
            if (error) {
                print_error(error);
                break;
            }
            continue;
        }

        /* if got here no save word represent the first word of the line, need to exit */
        break;
    }

    fclose(am_file);

}

/* HANDALING SYMBOL IN LINE */
int is_label(char *name, int *error, hash_table macros, hash_table symbols) {
    int len = strlen(name);

    printf("checking if '%s' is a label\n", name);

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

    /* checl the requirments of label name */
    if (len > 31 || !isalpha(name[0]) || !alpha_and_numeric_only_string(substring(name, 1, len-1))){
        return 0;
    }

    /* label name is fine and meets the requirments of label name */
    return 1;
}

void add_symbol(hash_table source, char *key, int count, int flag) {
    node symbol;
    struct symbol_value *value = malloc(sizeof(struct symbol_value));
    value->type = flag;
    value->count = count;

    symbol = create_node(key, value);
    insert(source, symbol);
}


/* HANDALING .DATA LINE */
void handle_data(char *arg, int *error) {
    char copy[MAX_LINE], *token;
    if (!check_data_arg(arg)) {
        *error = 3; /* 3: error in .data line arguments */
        return;
    }

    /* arguments of .data are valid, need to code them into memory */
    strcpy(copy, arg);
    token = strtok(arg, ",");

    while (token != NULL) {
        /* TO BE CONTINUED */

        token = strtok(NULL, ",");
    }
}

int check_data_arg(char *arg) {
    char curr[MAX_LINE];

    while (*arg != '\0') {
        /* building the number in string curr */
        while (*arg != ',') {
            strcat(curr, (char *)*arg);
        }
        if (!atoi(curr)) return 0;
        arg++;
        curr[0] = '\0';
    }

    return 1;
}

/* HANDALING .STRING LINE */
void handle_string(char *str, int *error) {
    char copy[MAX_LINE], *token;
    if (!check_string(str)) {
        *error = 4; /* 4: error in .string string */
        return;
    }

    /* if got here string is valid, need to code each char into memory */
    /* arguments of .data are valid, need to code them into memory */
    strcpy(copy, str);
    token = strtok(str, ",");

    while (token != NULL) {
        /* TO BE CONTINUED */

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
    return 1;
}

void handle_opcode(char *word, int *error) {
    printf("in handle_opcode() function\n");
}

