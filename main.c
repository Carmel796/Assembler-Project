#include "main.h"

/* TODO:
 * implement the Hash-Table + Hash-Function
 * functions for hash table: insert into table (index find with hash function?)
 * in macro_handle: getting the macro name from the line + insert into hash table
 */


int main(int argc, char *argv[]) {
    FILE *am_file = NULL;
    hash_table macros = {0};
    while(--argc > 0) {
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
