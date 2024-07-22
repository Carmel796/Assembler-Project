#include <stdio.h>
#include <stdlib.h>

#include "header.h"

int main(int argc, char *argv[]) {
    FILE *as_file, *am_file;
    while(--argc > 0) {
        printf("start pre-preccesing, fetching macros\n");
        as_file = fopen_with_ending(*++argv, ".as", "r");
        /* macro_search(FILE *as_file) - search for macro definition line-by-line, if found - adding them to the hashTable - add_to_hash(char *key, char *value) */

        printf("starting first pass\n");


        printf("starting scond pass\n");


        free(as_file);
        free(am_file);
    }

    printf("Done\n");
    return 0;
}
