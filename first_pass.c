#include "first_pass.h"

#include "error_handle.h"

void first_pass(char *am_file_name, hash_table symbols, hash_table macros) {
    FILE *am_file = fopen_with_ending(am_file_name, ".am", "r");
    char line[MAX_LINE], *token;
    int error = 0; /* error-code */

    while (fgets(line, MAX_LINE, am_file)) {
        line_validation(line, &error, symbols, macros);
        if (error) {
            /* an error accures, the error number will be in the error variable */
        } else {
            /* the line precceced perfectly */
        }
    }
}

int line_validation(char *line, int *error, hash_table symbols, hash_table macros) {
    char line_copy[MAX_LINE], *token;

    if (!line_size_check(line, MAX_LINE, error))
        return 0;

    strcpy(line_copy, line);
    token = strtok(line_copy, DELIMETERS);

    if (is_label(token, error, symbols, macros)) {
        return 1; /* is_label will continue to process the rest of the line in case of label. */
    }
    if (is_data(token, error) || is_string(token, error)) {
        return 1; /* is_data and is_string will continue to process the rest of the line in case of .data or .string.  */ */
    }
    if (is_entry(token, error) || is_extern(token, error)) {
        return 1; /* is_entry and is_extern will continue to process the rest of the line in case of .entry or .extern.  */
    }
    if (is_opcade(token, error)) {
        return 1; /* is_opcode will continue to process the rest of the line in case of opcode {mov, lea...} */
    }

    *error = 2; /* 2: not a saved word in the assebmly language... */
    return 0;
}

int is_label(char *word, int *error, hash_table symbols, hash_table macros) {
    char *rest;

    if (!check_label_name(word, error, symbols, macros)) {
        return 0; /* not a label... (if it is a label but the label name have error, check_label_name will notice in the error variable) */
    }

    /* if got here, we have a label definition, label-name: word, label-arg: rest */
    rest = strtok(NULL, DELIMETERS); /* now rest is the  */




}

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

