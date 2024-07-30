#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include "pre_proc.c"
#include "hashtable.c"


void handle_macro(char *line, int offset);
void add_to_hash(char *key, char *value);

#endif
