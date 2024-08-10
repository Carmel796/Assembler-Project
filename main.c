#include "main.h"

int main(int argc, char *argv[]) {
    while(--argc > 0) {
        hash_table macros = {0}, symbols = {0};
        printf("start pre-preccesing, fetching macros\n");

        /* macro_search(FILE *as_file) - search for macro definition line-by-line, if found - adding them to the hashTable - add_to_hash(char *key, char *value) */
        if (!macro_search(argv[argc], macros)) {
            continue;
        }

        printf("starting first pass\n");
        if (!first_pass(argv[argc], symbols, macros)) { /* if an error occur in first_pass, should move to next file */
            print_error(17, -1);
            continue;
        }
        

        printf("starting second pass\n");


        free_table(macros, 1);
        free_table(symbols, 0);
    }

    printf("Done\n");
    return 0;
}
