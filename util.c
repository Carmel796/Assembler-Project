#include "util.h"

FILE *fopen_with_ending(const char *source_file_name, const char *ending, const char *mode) {
    char *file_name = create_file_name_with_ending(source_file_name, ending);
    FILE *fp = NULL;
    fp = fopen(file_name, mode);
    if(fp == NULL) {
        perror("Error");
    }
    return fp;
}

char *create_file_name_with_ending(const char *source_file_name, const char *ending) {
    size_t len1 = strlen(source_file_name), len2 = strlen(ending);
    char *result = malloc(len1 + len2 + 1);
    if(result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(result, source_file_name);
    strcat(result, ending);
    free(result);

    return result;
}

void safe_malloc(size_t size) {
    /* how to implement this? */
}
