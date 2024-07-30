#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fopen_with_ending(const char *source_file_name, const char *ending, const char *mode);
char *create_file_name_with_ending(const char *source_file_name, const char *ending);

#endif