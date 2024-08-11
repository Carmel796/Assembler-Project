#ifndef UTIL_H
#define UTIL_H

#define MAX_LINE 82
#define ACTION_CODE_COUNT 16

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct instruction {
    char *name;
    int arg_count;
    int legal_src[4];
    int legal_dst[4];
};

FILE *fopen_with_ending(const char *source_file_name, const char *ending, const char *mode);
char *create_file_name_with_ending(const char *source_file_name, const char *ending);
char *strdup(const char *s);
void *safe_malloc(size_t size);
char *substring(const char* source, int start, int end);
int alpha_and_numeric_only_string(char *word);
void int_to_binary(int value, short *binary);
void print_binary(short value);
int linear_search(struct instruction arr[], int size, const char *target);
int is_all_zeros(int arr[], int size);
void print_array(const int arr[], int size);

#endif