#include "first_pass.h"

typedef struct symbol_value {
    int value; /* DC for .data or .string, IC for Instruction */
    int type; /*flag - 0: Data(.data or .string), 1: Instruction */
} symbol_value;

void first_pass(char *am_file_name, hash_table symbols, hash_table macros) {
    FILE *am_file = fopen_with_ending(am_file_name, ".am", "r");
    char line[MAX_LINE], *token;
    int error = 0, DC = 0, IC = 0; /* error-code */

    while (fgets(line, MAX_LINE, am_file)) {
        line_validation(line, &error, symbols, macros, &DC, &IC);
        if (error) {
            /* an error accures, the error number will be in the error variable */
        } else {
            /* the line precceced perfectly */
        }
    }
}

void line_validation(char *line, int *error, hash_table symbols, hash_table macros, int *DC, int *IC) {
    char line_copy[MAX_LINE], *token;
    int symbol_flag = 0; /* 0: no label definition currently, 1: there is label definition */

    if (!line_size_check(line, MAX_LINE, error))
        return;
    strcpy(line_copy, line);
    token = strtok(line_copy, DELIMETERS);

    if (is_label(token, error, symbols, macros)) {
        symbol_flag = 1; /* is_label will continue to process the rest of the line in case of label. */
    }
    if (error) /* eror acures in label definition (name / length / ...) */
        return;
    if (is_data(token, error, &symbol_flag, DC) || is_string(token, error, &symbol_flag, DC)) {
        return; /* is_data and is_string will continue to process the rest of the line in case of .data or .string.  */ */
    }
    if (is_entry(token, error) || is_extern(token, error)) {
        return; /* is_entry and is_extern will continue to process the rest of the line in case of .entry or .extern.  */
    }
    if (is_opcade(token, error, &symbol_flag, IC)) {
        return; /* is_opcode will continue to process the rest of the line in case of opcode {mov, lea...} */
    }

    *error = 2; /* 2: not a saved word in the assebmly language... */
    return;
}

int is_label(char *word, int *error, hash_table symbols, hash_table macros) {
    if (!check_label_name(word, error, symbols, macros)) {
        return 0; /* not a label... (if it is a label but the label name have error, check_label_name will notice in the error variable) */
    }

    /* if got here, we have a label definition, label-name: word, label-arg: rest */
    return 1;
}

/* return 0 in cases:
 * - not label definition
 * - error in label definition
 */
int check_label_name(char *word, int *error, hash_table symbols, hash_table macros) {
    int len = strlen(word);
    if (!strcmp(word[len-1], ":"))
        return 0;
    if (len > 31 || !isalpha(word[0]) || !alpha_and_numeric_only_string(substring(word, 1, len-1)) || search(symbols, word) || search(macros, word))
        *error = 4; /* 4: error in label name */
        return 0;
    return 1;
}

int line_size_check(char *line, int size, int *error) {
    if (strlen(line) > size) {
        *error = 1; /* 1: line too long */
        return 0;
    } return 1; /* length is ok */
}

int is_data(char *word, int *error, int *DC, int *is_symbol, char *symbol) {
    int *array, length = 0;
    char *token;
    if (strcmp(word, ".data")) {
        return 0; /* word is not .data */
    }

    /* word == .data, apply right actions */
    token = strtok(NULL, ",");
    if (is_symbol) {
        add_symbol(symbol, DC, 0);
    }
    array = malloc(sizeof(int));
    while (token != NULL) {
        length++;
        /* CONTINUE!!! */
    }

}



