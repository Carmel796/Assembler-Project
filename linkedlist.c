#include "linkedlist.h"

struct node {
    char *key;
    void *value;
    struct node *next;
};

void insert_node(char *key, void *value, node *root) {
    node new = create_node(key, value);
    if (*root == NULL)
        *root = new;
    else {
        node curr = *root;
        while(curr->next != NULL)
            curr = curr->next;

        curr->next = new;
    }
}

node create_node(char *key, void *value) {
    return;
}

node search_node(node root, char *key) {
    return;
}