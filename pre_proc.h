#ifndef PRE_PROC_H
#define PRE_PROC_H

#include <stdio.h>
#include <string.h>
#include "linkedlist.c"
#include "hashtable.c"

#define MAX_LINE 82

FILE *fopen_with_ending(char *source_file_name, char *ending, char *mode);
FILE *macro_search(FILE *as_file, FILE *am_file , hashtable macros);
char *get_macro_name(char *line_after_macr);
node *handle_macro(node *curr_line, char *line);
void add_macro_to_table(node *macro_to_add, hashtable *macros);

#endif