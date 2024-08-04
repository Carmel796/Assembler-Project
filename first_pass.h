#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include <stdio.h>
#include "hashtable.h"

void first_pass(FILE *am_file, hash_table macros, hash_table lables);
void handle_line(char *word, char *other);

#endif