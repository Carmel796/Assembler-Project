#ifndef UTIL_H
#define UTIL_H

#define MAX_LINE 82
#define ACTION_CODE_COUNT 16

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *action_code[] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};
FILE *fopen_with_ending(const char *source_file_name, const char *ending, const char *mode);
char *create_file_name_with_ending(const char *source_file_name, const char *ending);
char *strdup(const char *s);
void *safe_malloc(size_t size);
int action__code_search(char *word);

#endif