#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include <stdio.h>
#include "hashtable.h"
#include "error_handle.h"

#define MAX_SYMBOL_LENGTH 31

extern int DC, IC;
extern short data_image[4096];
extern short code_image[4096];

typedef enum {
 false, true
} bool;

void first_pass(char *am_file_name, hash_table symbols, hash_table macros);
int is_label(char *name, int *error, hash_table macros, hash_table symbols);
int check_symbol_name(char *name);
void add_symbol(hash_table source, char *key, int count, int flag);
void handle_data(char *arg, int *error);
bool check_comma(char *arg);
void handle_string(char *str, int *error);
int check_string(char *str);
void handle_extern(char *word, int *error);
void handle_entry(char *word, int *error);
int is_opcode(char *word);
void handle_opcode(char *word, int *error);


/* ERRORS:
 * 1: error in label name
 * 2: existing macro / symbol with the same name
 * 3: error in .data line arguments
 * 4: error in .string string
 * 5:
 */

#endif