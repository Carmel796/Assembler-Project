#include "linkedlist.h"

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

node create_node(char *key, void *value) { /* what CONST means? */
    node new_node = malloc(sizeof(node));
    new_node->key = strdup(key);

    new_node->value = value; /* Needs to be changed, cannot use strdup() when value is void* parameter */

    new_node->next = NULL;
    return new_node;
}

node search_node(node root, const char *key) {
    while (root != NULL)
        if (strcmp(get_key(root), key))
            root = get_next(root);
        else break;
    return root;
}

void fprint_linked_list(FILE *output, node list) {
    while (list != NULL) {
        fprintf(output, "%s", get_key(list));
        list = get_next(list);
    }
}

node get_next(node curr) {
    return curr->next;
}

const char *get_key(const node curr) {
    return curr->key;
}

void set_next(node curr, node next) {
    curr->next = next;
}

void *get_value(node curr) {
    return curr->value;
}