#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

typedef struct node *node;
void insert_node(char *key, void *value, node *root);
node create_node(char *key, void *value);
node search_node(node root, const char *key);
void fprint_linked_list(FILE *output, node list);
void *add_value(node source, void *value);
node copy_list(node source);
node get_next(node curr);
const char *get_key(node curr);
void set_next(node curr, node next);
void *get_value(node curr);
void free_list(node head, void (*free_value)(void *), int flag);
void free_nested_list(void *value);
void set_value(node curr, void *value);

#endif
