#ifndef PRE_PROC_H
#define PRE_PROC_H

#include <stdio.h>
#include <string.h>
#include "hashtable.h"
#include "util.h"
#include "error_handle.h"



int macro_search(char *file_name, hash_table macros, int *main_error);
char *get_macro_name(char *line_after_macr);
void handle_macro(node *curr_line, char *line);

#endif