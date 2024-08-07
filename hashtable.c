#include "hashtable.h"

/* djb2 */
unsigned long hash(const unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % HASH_TABLE_SIZE;
}

void insert(hash_table source, const node to_insert) {
    unsigned long index = hash((const unsigned char *)get_key(to_insert));
    node curr = *(source + index);
    if (curr == NULL)
        *(source + index) = to_insert;

    else {
        while (get_next(curr) != NULL) {
            curr = get_next(curr);
        }
        set_next(curr, to_insert);
    }
}

void *search(const hash_table source,const char *key) {
    unsigned long index = hash((const unsigned char *)key);
    node found = search_node(*(source + index), key);
    return found ? get_value(found) : NULL;
}

void free_table(hash_table src, int flag) {
    int i;
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        if (flag) free_list(src[i], free_list);
        else free_list(src[i], NULL);
    }
}
