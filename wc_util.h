#ifndef WCUTIL_H
#define WCUTIL_H

#include <stddef.h>

char* read_file(char filename[]);

int inword(char c);
int inword_first(char c);

char *make_word(char *text, size_t first, size_t last);

char *strdup(char *source);
char *lowercase(char *source);
int strcmp_case_insensitive(char *a, char *b);
int compare_strings_lower(const void *a, const void *b);

#endif
