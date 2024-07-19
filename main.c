#include <stdio.h>
#include "header.h"

int main(int argc, char *argv[]) {
    FILE *as_file, *am_file;
    while(--argc > 0) {
        printf("start pre-preccesing, fetching macros\n");
        as_file = fopen_with_ending(argv[argc], ".as");

        printf("starting first pass\n");


        printf("starting scond pass\n");
    }

    printf("Done\n");
    return 0;
}
