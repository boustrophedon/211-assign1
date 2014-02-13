#ifndef WORDOCCURS_H
#define WORDOCCURS_H

#include <stddef.h>

#include "wordlist.h"

#define OLD 0
#define NEW 1

typedef struct occurrence {
	wordlist *words;
	char *lower;
	size_t total;
	size_t uniq; /* this isn't strictly necessary as we can do wl_size(wo->words) */
} wordoccur;

typedef struct occurrences {
	wordoccur **wo_arr; /* array of pointers to wordoccurs */
	size_t size;
} occurlist;

occurlist *ol_create(wordlist *wl);
void ol_delete(occurlist *ol);
void ol_add_words(occurlist *ol, wordlist *wl);
wordoccur *ol_get(occurlist *ol, size_t index);
void ol_print(occurlist *ol);

wordoccur *wo_create(char *word);
void wo_delete(wordoccur *wo);
void wo_update(wordoccur *wo, char *word);
char *wo_get(wordoccur *wo, size_t index);

#endif
