#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


FILE *fopen_with_ending(char *source_file_name, char *ending) {
    size_t len1 = strlen(source_file_name), len2 = strlen(ending);
    char *result = malloc(len1 + len2 + 1);
    if(result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(result, source_file_name);
    strcat(result, ending);

    return fopen(result, "r");
}
