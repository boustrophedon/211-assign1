#ifndef WCUTIL_H
#define WCUTIL_H

#include <stddef.h>

char* read_file(char filename[]);

int inword(char c);
int inword_first(char c);

char *make_word(char *text, size_t first, size_t last);

char *lowercase(char *source);
int compare_strings_lower(const void *a, const void *b);

#endif
