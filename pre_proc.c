#include "pre_proc.h"

int macro_search(char *file_name, hash_table macros, int *main_error) { /* creating new .as file, every line thats not macro decleration or body - add to new file */
    node curr_line = NULL, curr_macro = NULL, curr_value = NULL;
    FILE *as_file = fopen_with_ending(file_name, ".as", "r");
    char line[MAX_LINE] = {0}, word[MAX_LINE] = {0};
    int offset = 0, macro_flag = 0, line_count = -1;
    FILE *am_file = fopen_with_ending(file_name, ".am", "w");
    if (as_file == NULL || am_file == NULL) {
        print_error(22, 0);
        return 0;
    }
    while(fgets(line, MAX_LINE, as_file)) {
        line_count++;
        if (!length_check(line, main_error)) return 0;

        if (sscanf(line, "%s%n", word, &offset) == 1) {
            if (!strcmp(word, "endmacr")) {
                macro_flag = 0;
                if (!empty_line(line + offset)) { /* another word in "endmacr" line */
                    print_error(6, line_count);
                    return 0;
                }
                insert(macros, curr_macro);
                curr_line = NULL;
                curr_value = NULL;
                curr_macro = NULL;
            }
            else if (macro_flag) {
                handle_macro(&curr_line, line);
            }
            else if (!strcmp(word, "macr")) { /* not allowed macro inside a macro definitaon so this approch will work */
                if (!check_macr(line + offset, line_count, macros)) {
                    return 0;
                }
                macro_flag = 1;
                insert_node(get_macro_name(line + offset), (curr_line = create_node("", NULL)), &curr_macro);
            }
            else if ((curr_value = search(macros, word))) {
                if (!empty_line(line + offset)) { /* macro call line has more chars after than the macro-call */
                    print_error(7, line_count);
                    return 0;
                }
                fprint_linked_list(am_file, curr_value);
            }
            else {
                if (*word != ';')
                    fprintf(am_file, "%s", line);
            }
        }
    }

    fclose(as_file);
    fclose(am_file);
    return 1; /* success*/
}

char *get_macro_name(char *line_after_macr){
    char *macro_name = safe_malloc(sizeof(char) * MAX_LINE);
    sscanf(line_after_macr, "%s", macro_name);
    return macro_name;
}

void handle_macro(node *curr_line, char *line) {
    insert_node(line, NULL, curr_line);
    *curr_line = get_next(*curr_line);
}


