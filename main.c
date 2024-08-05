#include "main.h"

int main(int argc, char *argv[]) {
    while(--argc > 0) {
        hash_table macros = {0}, symbol_table = {0};
        FILE *am_file = NULL;
        printf("start pre-preccesing, fetching macros\n");

        /* macro_search(FILE *as_file) - search for macro definition line-by-line, if found - adding them to the hashTable - add_to_hash(char *key, char *value) */
        if (!(am_file = macro_search(argv[argc], macros))) { /* as_file or am_file failed to open */
            printf("faied to open .as file or .am file\n");
        }

        printf("starting first pass\n");
        /*first_pass(am_file, macros, symbol_table);*/


        printf("starting scond pass\n");
    }

    printf("Done\n");
    return 0;
}
