#ifndef PRE_PROC_H
#define PRE_PROC_H

#include <stdio.h>
#include <string.h>
#include "hashtable.h"

#define MAX_LINE 82

FILE *fopen_with_ending(char *source_file_name, char *ending, char *mode);
FILE *macro_search(FILE *as_file, FILE *am_file , hashtable macros);
void handle_macro(char *line_after_macr);

#endif