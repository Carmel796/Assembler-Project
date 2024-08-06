#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#define DELIMETERS " \t\r\v\n\f\0"
#define MAX_LABEL_LINE 32

#include <stdio.h>
#include "hashtable.h"
#include "error_handle.h"

void first_pass(char *am_file_name, hash_table symbol_table);
void line_validation(char *line, int *error, hash_table symbols, hash_table macros, int *DC, int *IC);
int is_label(char *word, int *error, hash_table symbols, hash_table macros);
int line_size_check(char *line, int size, int *error);
int check_label_name(char *word, int *error, hash_table symbol_table, hash_table macros);
int is_data(char *word, int *error, int *DC, int *is_symbol, char *symbol);
#endif