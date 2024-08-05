#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include <stdio.h>
#include <ctype.h>
#include "hashtable.h"
#include "label_value.h"


void first_pass(FILE *am_file, hash_table macros, hash_table symbol_table);
int is_symbol(char *word, hash_table symbol_table);
void handle_symbol(hash_table symbol_table, char *name, char *line);
void handle_action_line(char *word, char *arg);


#endif