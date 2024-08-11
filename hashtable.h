#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "linkedlist.h"
#define HASH_TABLE_SIZE 100

typedef node hash_table[HASH_TABLE_SIZE];
unsigned long hash(const unsigned char *str);
void insert(hash_table source, const node to_insert);
void *search(const hash_table source, const char *key);
void free_table(hash_table src, int flag);
void update_data_values(const hash_table table, const int IC);


#endif