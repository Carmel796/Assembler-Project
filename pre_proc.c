#include "pre_proc.h"

FILE *macro_search(char *file_name, hash_table macros) { /* creating new .as file, every line thats not macro decleration or body - add to new file */
    node curr_line = NULL, curr_macro = NULL, curr_value = NULL;
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
                printf("saw endmacr\n");
                macro_flag = 0;
                insert(macros, curr_macro);
            }
            else if (macro_flag) {
                printf("macro line: %s\n", line);
                handle_macro(&curr_line, line);
            }
            else if (!strcmp(word, "macr")) { /* not allowed macro inside a macro definitaon so this approch will work */
                printf("saw macr\n");
                macro_flag = 1;
                curr_line = create_node("line head", NULL);
                curr_macro = create_node("m_macr", curr_line);
            }
            else if ((curr_value = search(macros, word))) {
                fprint_linked_list(am_file, curr_value);
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

char *get_macro_name(char *line_after_macr){
    char *macro_name = malloc(sizeof(char) * MAX_LINE);
    printf("got the macro name");
    sscanf(line_after_macr, "%s", macro_name);
    return macro_name;
}

void handle_macro(node *curr_line, char *line) {
    insert_node(line, NULL, curr_line);
    *curr_line = get_next(*curr_line);
}

