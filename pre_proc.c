#include "pre_proc.h"

FILE *macro_search(char *file_name, hashtable macros) { /* creating new .as file, every line thats not macro decleration or body - add to new file */
    /*
     * char line[80]
     * create new .am file - ?malloc size?
     * while(fgets(line, sizeof(line), as_file)
     * if macro_dec_line(line): loop until strcmp(line, "endmcr") to save macro name + body, then add_to_hash(mcr_name, mce_body) ?malloc?
     * else: add line to new file
     */

    FILE *as_file = fopen_with_ending(file_name, ".as", "r");
    FILE *am_file = fopen_with_ending(file_name, ".am", "w");
    char line[MAX_LINE], word[MAX_LINE] = {0};
    int offset = 0;
    if (!as_file || !am_file) {
        return NULL;
    }
    while(fgets(line, MAX_LINE, as_file)) {
        if (sscanf(line, "%s%n", word, &offset) == 1) {
            if (!strcmp(word, "macr")) {
                handle_macro(line + offset);
            }
            else if (hash_search(macros, word)) {

            }
            else {
                fprintf(am_file, "%s", line);
            }
        }
    }
}

void handle_macro(char *line_after_macr) {
    char macro_name[MAX_LINE];
    sscanf(macro_name, "%s", line_after_macr);
}

void add_to_hash(char *key, char *value) {

}