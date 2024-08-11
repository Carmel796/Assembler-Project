#ifndef SECOND_PASS_H
#define SECONF_PASS_H

#include <stdio.h>
#include "first_pass.h"

int second_pass(char *am_file_name, hash_table symbols);
void activate_entry(hash_table symbols, char *arg, int *error);

#endif