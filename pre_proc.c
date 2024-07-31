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
                macro_flag = 0;
                insert(macros, curr_macro);
            }
            else if (macro_flag) {
                handle_macro(&curr_line, line);
            }
            else if (!strcmp(word, "macr")) { /* not allowed macro inside a macro definitaon so this approch will work */
                macro_flag = 1;
                insert_node(get_macro_name(line), (curr_line = create_node("", NULL)), &curr_macro);
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

char *get_macro_name(char *line_after_macr) {
    char temp[MAX_LINE];
    char *macro_name = malloc((strlen(temp) + 1) * sizeof(char));/* Temporary buffer to hold the extracted word */
    if (sscanf(line_after_macr, "%s", temp) != 1) {
        return NULL; /* If sscanf fails to read a word, return NULL */
    }

    /* Allocate memory for the resulting string */
    if (macro_name == NULL) {
        return NULL; /* If memory allocation fails, return NULL */
    }

    /* Copy the word into the allocated memory */
    strcpy(macro_name, temp);

    /* Return the dynamically allocated string */
    return macro_name;
}

void handle_macro(node *curr_line, char *line) {
    insert_node(line, NULL, curr_line);
    *curr_line = get_next(*curr_line);
}

