#include "readfile.h"

#define BUF_SIZE 17


char *readline(const char *prompt) {
    printf("%s", prompt);
    char *input = calloc(1, sizeof(char));
    char buf[17];
    int f = 0;
    while ((f = scanf("%16[^\n]", buf))) {
        if (f == EOF) {
            free(input);
            return NULL;
        }
        input = realloc(input, (strlen(input) + strlen(buf) + 1) * sizeof(char));
        strcat(input, buf);
    }
    scanf("%*c");
    return input;
}



char *file_readline(FILE *file) {
    char *input = calloc(1, sizeof(char));
    char buf[BUF_SIZE];
    int f = 0;
    while ((f = fscanf(file, "%16[^\n]", buf))) {
        if (f == EOF) {
            free(input);
            return NULL;
        }
        input = realloc(input, (strlen(input) + strlen(buf) + 1) * sizeof(char));
        strcat(input, buf);
    }
    fscanf(file , "%*c");
    return input;
}
