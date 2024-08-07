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

/* returns a new node with key and value allocated by the user */
node create_node(char *key, void *value) { /* what CONST means? */
    node new_node = safe_malloc(sizeof(node));
    new_node->key = key;

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

/* gets: node head and frees all subsequens node */
void free_list(node head, void (*free_value)(void *)) {
    while(head != NULL) {
        node temp = head;
        free(head->key);
        if (free_value == NULL) {
            free(head->value);
        } else {
            free_value(head->value);
        }
        head = head->next;
        free(temp);
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