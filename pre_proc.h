#ifndef PRE_PROC_H
#define PRE_PROC_H

#include <stdio.h>
#include <string.h>
#include "linkedlist.h"
#include "hashtable.h"
#include "util.h"

#define MAX_LINE 82

FILE *macro_search(char *file_name, hash_table macros, FILE *am_file);
char *get_macro_name(char *line_after_macr);
void handle_macro(node *curr_line, char *line);

#endif