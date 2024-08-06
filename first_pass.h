#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#define DELIMETERS " \t\r\v\n\f\0"
#define MAX_LABEL_LINE 32

#include <stdio.h>
#include "hashtable.h"

void first_pass(char *am_file_name, hash_table symbol_table);
int line_validation(char *line, int *error);
int is_label(char *word, int *error);
int line_size_check(char *line, int size. int *error);
int check_label_name(char *word, int *error);

#endif