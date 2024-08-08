#include "error_handle.h"

#include <ctype.h>

int empty_line(char *line){
    while (*line != '\0') {
        if (!isspace(*line)) return 0;
        line++;
    }
    return 1;
}

void print_error(int error_num) {
    printf("error number: %d\n", error_num);
}