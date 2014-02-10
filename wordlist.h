#ifndef WORDLIST_H
#define WORDLIST_H

#include <stdlib.h>

#define INITIAL_SIZE 5

typedef struct wl_vector {
    char **arr; /* array of strings */
    size_t array_size; /* internal use only */
    size_t num_elements;
} wordlist;

wordlist *wl_create();
int wl_grow(wordlist *wl); /* double size, only call from wl_append */
int wl_append(wordlist *wl, char *word);
char *wl_get(wordlist *wl, size_t index);
int wl_set(wordlist *wl, size_t index, char *word); /* I don't think I'll actually need this for this assignment so I am leaving it unimplemented */

size_t wl_size(wordlist *wl); /* returns number of elements i.e. how far have we advanced in the list, rather than internal size of array */

#endif /* WORDLIST_H */
