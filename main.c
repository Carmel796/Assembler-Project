#include "main.h"

int main(int argc, char *argv[]) {
    FILE *am_file = NULL;
    hash_table macros;
    while(--argc > 0) {
        macros = {0}; /* for every file new macros table */
        printf("start pre-preccesing, fetching macros\n");

        /* macro_search(FILE *as_file) - search for macro definition line-by-line, if found - adding them to the hashTable - add_to_hash(char *key, char *value) */
        if (!macro_search(argv[argc], macros, am_file)) { /* as_file or am_file failed to open */
            printf("faied to open .as file or .am file\n");
        }

        printf("starting first pass\n");
        /*first_pass(am_file, macros);*/


        printf("starting scond pass\n");
    }

    printf("Done\n");
    return 0;
}
