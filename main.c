#include "main.h"

/* TODO:
 * implement the Hash-Table + Hash-Function
 * functions for hash table: insert into table (index find with hash function?)
 * in macro_handle: getting the macro name from the line + insert into hash table
 */


int main(int argc, char *argv[]) {
    while(--argc > 0) {
        printf("start pre-preccesing, fetching macros\n");

        hash_table macros = {0};

        /* macro_search(FILE *as_file) - search for macro definition line-by-line, if found - adding them to the hashTable - add_to_hash(char *key, char *value) */
        if (!macro_search(argv[argc], macros)) { /* as_file or am_file failed to open */
            /* skip to next file */
        }

        printf("starting first pass\n");


        printf("starting scond pass\n");
    }

    printf("Done\n");
    return 0;
}
