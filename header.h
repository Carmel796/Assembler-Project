#ifndef HEADER_H
#define HEADER_H

FILE *fopen_with_ending(char *source_file_name, char *ending, char *mode);
FILE *macro_search(FILE *as_file, FILE *am_file , hash_table macros);
void handle_macro(char *line, int offset);
void add_to_hash(char *key, char *value);

#endif
