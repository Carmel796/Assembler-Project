#include "pre_proc.h"

FILE *macro_search(char *file_name, hashtable *macros) { /* creating new .as file, every line thats not macro decleration or body - add to new file */

    node curr_line, curr_macro;
    FILE *as_file = fopen_with_ending(file_name, ".as", "r");
    FILE *am_file = fopen_with_ending(file_name, ".am", "w");
    char line[MAX_LINE], word[MAX_LINE] = {0};
    int offset = 0, macro_flag = 0;
    if (!as_file || !am_file) {
        return NULL;
    }
    while(fgets(line, MAX_LINE, as_file)) {
        if (sscanf(line, "%s%n", word, &offset) == 1) {
            if (!strcmp(word, "endmacr")) {
                macro_flag = 0;
                add_macro_to_table(&curr_macro, macros);
                free(curr_line); /* EXPLENATION: about free(), and when to use */
                free(curr_macro);
            }
            else if (macro_flag) {
                curr_line = *handle_macro(&curr_line, line);
            }
            else if (!strcmp(word, "macr")) { /* not allowed macro inside a macro definitaon so this approch will work */
                macro_flag = 1;
                curr_line = *create_node("", NULL);
                curr_macro = *create_node(get_macro_name(line), curr_line);
            }
            else if (hash_search(*macros, word)) {
                /* put together the macro-body, whose wplitted into nodes (key = line) in the macro value. */
            }
            else {
                fprintf(am_file, "%s", line);
            }
        }
    }

    fclose(as_file);
    fclose(am_file);

    return am_file;
}

char *get_macro_name(char *line_after_macr) {
    char macro_name[MAX_LINE];
    sscanf(macro_name, "%s", line_after_macr);
    return macro_name; /* can i return value of variable declared inside of a function? */
}

node *handle_macro(node curr_line, char *line) {
    node next_line = *create_node(line, NULL);
    curr_line->next = next_line;

    return &next_line;
}

void add_macro_to_table(node *macro_to_add, hashtable *macros) {

}
