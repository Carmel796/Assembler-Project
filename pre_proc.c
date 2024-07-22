#include <stdio.h>
#include <string.h>

#include "header.h"

#define MAXLINE 82

FILE *macro_search(FILE *as_file, FILE *am_file , hash_table macros) { /* creating new .as file, every line thats not macro decleration or body - add to new file */
    /*
     * char line[80]
     * create new .am file - ?malloc size?
     * while(fgets(line, sizeof(line), as_file)
     * if macro_dec_line(line): loop until strcmp(line, "endmcr") to save macro name + body, then add_to_hash(mcr_name, mce_body) ?malloc?
     * else: add line to new file
     */

    char line[MAXLINE], word[MAXLINE] = {0};
    int offset = 0;
    while(fgets(line, MAXLINE, as_file)) {
        if (sscanf(line, "%s%n", word, &offset) == 1) {
            if (!strcmp(word, "macr")) {
                handle_macro(line, offset);
            }
            else if (hash_search(macros, word)) {

            }
            else {
                fprintf(am_file, "%s", line);
            }
        }
    }
}

void handle_macro(char *line, int offset) {
    return;
}

void add_to_hash(char *key, char *value) {

}