#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include <stdio.h>
#include "hashtable.h"
#include "error_handle.h"

#define MAX_SYMBOL_LENGTH 31
#define OPCODE_ARRAY_SIZE 16
#define COMMA_DELIM ","

extern int DC, IC;
extern short data_image[4096];
extern short code_image[4096];

typedef enum {
 false, true
} bool;

struct symbol_value {
 int type; /* 0: data, 1: opcode */
 int count; /* DC for data, IC for opcode */
};

extern struct instruction opcode_array[];


void first_pass(char *am_file_name, hash_table symbols, hash_table macros);
int is_label(char *name, int *error, hash_table macros, hash_table symbols);
int check_symbol_name(char *name);
void add_symbol(hash_table symbols, char *key, int count, int flag);
void handle_data(char *arg, int *error);
bool check_comma(const char *arg);
void handle_string(char *str, int *error);
int check_string(char *str, int *s_index, int *e_index);
void handle_extern(char *word, int *error);
void handle_entry(char *word, int *error);
int is_opcode(char *word);
void handle_opcode(char *opcode, char *arg, int *error, hash_table symbols);
int check_data_num(char *str);
int get_arg_count(int opcode_index);
void set_bit_to_one(short *src, int index);
int check_operand(char *token);
int check_register_name(char *name);
int get_number_from_operand(char *token);

#endif