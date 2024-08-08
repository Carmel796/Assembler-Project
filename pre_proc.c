#include "pre_proc.h"

#include "first_pass.h"

int macro_search(char *file_name, hash_table macros) { /* creating new .as file, every line thats not macro decleration or body - add to new file */
    node curr_line = NULL, curr_macro = NULL, curr_value = NULL;
    FILE *as_file = fopen_with_ending(file_name, ".as", "r");
    char line[MAX_LINE], word[MAX_LINE] = {0};
    int offset = 0, macro_flag = 0;
    FILE *am_file = fopen_with_ending(file_name, ".am", "w");
    if (!as_file || !am_file) {
        return 0;
    }
    while(fgets(line, MAX_LINE, as_file)) {
        if (sscanf(line, "%s%n", word, &offset) == 1) {
            if (!strcmp(word, "endmacr")) {
                printf("saw endmacr\n");
                macro_flag = 0;
                insert(macros, curr_macro);
                curr_line = NULL;
                curr_value = NULL;
                curr_macro = NULL;
            }
            else if (macro_flag) {
                handle_macro(&curr_line, line);
            }
            else if (!strcmp(word, "macr")) { /* not allowed macro inside a macro definitaon so this approch will work */
                if (!check_macr(line + offset, macros)) {
                    return 0;
                }
                macro_flag = 1;
                insert_node(get_macro_name(line + offset), (curr_line = create_node("", NULL)), &curr_macro);
            }
            else if ((curr_value = search(macros, word))) {
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
    printf("got the macro name\n");
    sscanf(line_after_macr, "%s", macro_name);
    return macro_name;
}

void handle_macro(node *curr_line, char *line) {
    insert_node(line, NULL, curr_line);
    *curr_line = get_next(*curr_line);
}

int check_macr(char *line_after_macr, hash_table macros) {
    char macro_name[MAX_LINE];
    int offset = 0;
    sscanf(line_after_macr, "%s%n", macro_name, &offset);

    if (!empty_line(line_after_macr + offset)) return 0;

    if (search(macros, macro_name) != NULL || is_opcode(macro_name)) {
        printf("*already macro with the same name || macro name is one of the 16 opcodes\n");
        return 0;  /*already macro with the same name || macro name is one of the 16 opcodes*/
    }
    return 1;
}

