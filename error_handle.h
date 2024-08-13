#ifndef ERROR_HANDLE_H
#define ERROR_HANDLE_H

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "first_pass.h"

extern const char *error_messages[];

int empty_line(char *line);
void print_error(int error_num, int line);
int check_macr(char *line_after_macr, int line_count, hash_table macros);
int length_check(char *line, int max, int *error);

#endif
