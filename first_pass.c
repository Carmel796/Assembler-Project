#include "first_pass.h"

void first_pass(FILE *am_file, hash_table macros, hash_table lables) {
    char buffer[MAX_LINE] = "mov r1,r2";
    while (fgets(buffer, MAX_LINE, am_file)) {
        char *first_word = safe_malloc(MAX_LINE);
        int offset, action_code_number;
        sscanf(first_word, "%s%n", buffer, &offset);
        if ((action_code_number = action__code_search(first_word)) != -1) {
            handle_line(first_word, buffer + offset);
        }

    }
}

void handle_line(char *word, char *other) {

}
