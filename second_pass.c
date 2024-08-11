#include "second_pass.h"

/* -- THIS IS SECOND PASS -- */
int second_pass(char *am_file_name, hash_table symbols) {
    FILE *am_file = fopen_with_ending(am_file_name, ".am", "r");
    char line[MAX_LINE] = {0}, word_buffer[MAX_LINE] = {0};
    int error = 0, offset, total_offset, line_index = -1;
    IC = 0;

    while (fgets(line, MAX_LINE, am_file)) {
        /* Initials */
        word_buffer[0] = '\0';
        offset = 0;
        total_offset = 0;
        error = 0;
        line_index++;


        if (!sscanf(line, "%s%n", word_buffer, &offset))
            continue;

        total_offset += offset;

        if (search(symbols, word_buffer)) { /* first word is label */
            sscanf(line + total_offset, "%s%n", word_buffer, &offset);
            total_offset += offset;
        }

        /* if got here: word_buffer should hold the first word of the line (after label if have) */
        if (!strcmp(word_buffer, ".data") || !strcmp(word_buffer, ".string") || !strcmp(word_buffer, ".extern")) continue;

        if (!strcmp(word_buffer, ".entry")) {
            sscanf(line + total_offset, "%s%n", word_buffer, &offset);
            activate_entry(symbols, word_buffer, &error);
            total_offset += offset;
        }

        else { /* opcode word */

        }

        if (error) {
            print_error(error, line_index);
        }

    }
    return 1;
}

void activate_entry(hash_table symbols, char *arg, int *error) {
    struct symbol_value *value;
    value = search(symbols, arg);
    if (value == NULL) {
        *error = 19;
        return;
    }
    value->type[3] = 1;
}

