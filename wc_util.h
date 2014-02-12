#ifndef WCUTIL_H
#define WCUTIL_H

#include <stddef.h>

char* read_file(char filename[]);

int inword(char c);
int inword_first(char c);

char *make_word(char *text, size_t first, size_t last);

#endif
