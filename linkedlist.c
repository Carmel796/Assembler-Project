#include "linkedlist.h"

#include <string.h>

struct node {
    char *key;
    void *value;
    struct node *next;
};

void insert_node(char *key, void *value, node *root) {
    node new = create_node(key, value); /* what CONST means? */
    if (*root == NULL)
        *root = new;
    else {
        node curr = *root;
        while(curr->next != NULL)
            curr = curr->next;

        curr->next = new;
    }
}

node *create_node(char *key, void *value) { /* what CONST means? */
    node new_node = malloc(sizeof(node));
    new_node->key = strdup(key);
    new_node->value = strdup(value); /* Needs to be changed? */
    new_node->next = NULL;
    return &new_node;
}

node search_node(node root, char *key) {
    return;
}