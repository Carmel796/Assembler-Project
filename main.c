#include "main.h"

int main(int argc, char *argv[]) {
    while(--argc > 0) {
        hash_table macros = {0}, symbols = {0};
        printf("start pre-preccesing, fetching macros\n");

        /* macro_search(FILE *as_file) - search for macro definition line-by-line, if found - adding them to the hashTable - add_to_hash(char *key, char *value) */
        if (!macro_search(argv[argc], macros)) { /* as_file or am_file failed to open */
            printf("faied to open .as file or .am file\n");
            continue;
        }

        printf("starting first pass\n");
        first_pass(argv[argv], macros, symbols, macros);


        printf("starting scond pass\n");
    }

    printf("Done\n");
    return 0;
}
