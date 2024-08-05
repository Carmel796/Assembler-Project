#include "first_pass.h"

#include <ctype.h>


void first_pass(FILE *am_file, hash_table macros, hash_table symbol_table) {
    char buffer[MAX_LINE];
    int IC = 0, DC = 0;
    while (fgets(buffer, MAX_LINE, am_file)) {
        char *first_word = safe_malloc(MAX_LINE);
        int offset, action_code_number;
        sscanf(first_word, "%s%n", buffer, &offset);
        if (is_symbol(first_word, symbol_table) == 1) { /* if os_symbol == -1: ERROR */
            handle_symbol(symbol_table ,substring(first_word, 0, strlen(first_word)-1), buffer + offset);
        } else if (is_data_instruction(first_word)) {

        } else if (is_entry_or_extern(first_word)) {

        } else if ((action_code_number = action_code_search(first_word)) != -1) {
            handle_action_line(first_word, buffer + offset);
        }

    }
}
/* gets: first word of assembly line,
 * returns:
        1 if legal symbol name,
        0 if not symbol (no : at word last character)
        -1 if illegal symbol name || symbol-name alreasy exists in symbol-table.
*/
int is_symbol(char *word, hash_table symbol_table) {
    int len = strlen(word);
    if (!strcmp(word[len-1], ":"))
        return 0;
    if (len > 31 || !isalpha(word[0]) || !alpha_and_numeric_only_string(substring(word, 1, len-1)) || search(symbol_table, word))
        return -1;
    return 1;
}


void handle_symbol(hash_table symbol_table, char *name, char *line) {
    char type[MAX_LINE];
    int offset;
    sscanf(type, "%s%n", line, &offset);
    if (!strcmp(type, ".data") || !strcmp(type, ".string")) { /* 5-7 lines in first-pass skeleton */
        /* function to handle .data or .string instruction */
    } else if (!strcmp(type, ".entry") || !strcmp(type, ".extern")) { /* 8-9 lines in first-pass skeleton */
        /* function to handle .entry or .extern instruction */
    } else if (action_code_search(type) != -1) { /* 10-13 lines in frist-pass skeleton */
        handle_action_line(type, line + offset);
    }
}

/* 10-13 lines in frist-pass skeleton */
void handle_action_line(char *word, char *arg) {

}
