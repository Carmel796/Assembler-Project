#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node *node;
void insert_node(char *key, void *value, node *root);
node create_node(char *key, void *value);
node search_node(node root, char *key);
node get_next(node curr);
const char *get_key(node curr);
void set_next(node curr, node next);
void *get_value(node curr);

#endif
