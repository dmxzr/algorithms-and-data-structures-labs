#ifndef READ_FILE_H
#define READ_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIM " \t"

char *readline(const char *prompt);
char *file_readline(FILE *file);

#endif /* READ_FILE_H */
