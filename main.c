#include "main.h"

int main(int argc, char *argv[]) {
    while(--argc > 0) {
        hash_table macros = {0}, symbols = {0};
        int error = 0;
        printf(COLOR "start pre-preccesing, fetching macros\n" RESET);

        /* macro_search(FILE *as_file) - search for macro definition line-by-line, if found - adding them to the hashTable - add_to_hash(char *key, char *value) */
        if (!macro_search(argv[argc], macros, &error)) {
            print_error(error, -1);
            continue;
        }

        printf(COLOR "starting first pass\n" RESET);
        if (!first_pass(argv[argc], symbols, macros)) { /* if an error occur in first_pass, should move to next file */
            print_error(17, -1);
            continue;
        }
        

        printf(COLOR "starting second pass\n" RESET);
        if (!second_pass(argv[argc], symbols)) {
            print_error(18, -1);
            continue;
        }


        free_table(macros, 1);
        free_table(symbols, 0);
    }

    printf(COLOR "Done\n" RESET);
    return 0;
}
