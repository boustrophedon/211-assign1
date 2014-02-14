#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "occurlist.h"
#include "wordlist.h"
#include "wc_util.h"


occurlist *ol_create(wordlist *wl) {
	occurlist *new_ol = malloc(sizeof(occurlist));
	new_ol->wo_arr = malloc(wl_size(wl) * sizeof(wordoccur*));
	new_ol->size = 0;

	for (size_t i = 0; i < wl_size(wl); i++ ){
		(new_ol->wo_arr)[i] = NULL;
	}

	ol_add_words(new_ol, wl);

	return new_ol;
}

void ol_delete(occurlist *ol) {
	for (size_t i = 0; i < ol->size; i++) {
		wo_delete(ol_get(ol, i));
	}
	free(ol->wo_arr);
	free(ol);
}

wordoccur *ol_add_word(occurlist *ol, char *word) {
	wordoccur *cur_wo = wo_create(word);
	(ol->wo_arr)[ol->size] = cur_wo;
	ol->size += 1;

	return cur_wo;
}

wordoccur *ol_add_cur_word(occurlist *ol, wordoccur *cur_wo, char *word) {
	if (strcmp_case_insensitive(cur_wo->lower, word) == 0) {
		wo_update(cur_wo, word);
	}
	else {
		cur_wo = ol_add_word(ol, word);
	}
	return cur_wo;
}

void ol_add_words(occurlist *ol, wordlist *wl) {
	char *word = wl_get(wl, 0);
	wordoccur *cur_wo = ol_add_word(ol, word);

	for (size_t i = 1; i < wl_size(wl); i++) {
		word = wl_get(wl, i);
		cur_wo = ol_add_cur_word(ol, cur_wo, word);
	}
}

wordoccur *ol_get(occurlist *ol, size_t index) {
	if (index < ol->size) {
		return (ol->wo_arr)[index];
	}
	else {
		return NULL;
	}
}

void ol_print(occurlist *ol) {
	printf("Word	Total No. Occurences	No. Case-Sensitive Versions\n");
	for (size_t i = 0; i < ol->size; i++) {
		wordoccur *wo = ol_get(ol, i);
		printf("%s\t%zu\t%zu\n", wo->lower, wo->total, wo->uniq);
	}
}

wordoccur *wo_create(char *word) {
	wordoccur *new_wo = malloc(sizeof(wordoccur));

	new_wo->words = wl_create();
	/* make a duplicate so that when we free word from the original wl
	 * we don't also free the word in our ol/wo
	 */
	wl_append(new_wo->words, str_dup(word));

	new_wo->lower = lowercase(word);

	new_wo->total = 1;
	new_wo->uniq = 1;

	return new_wo;
}

void wo_delete(wordoccur *wo) {
	wl_delete(wo->words);
	free(wo->lower);
	free(wo);
}

void wo_update(wordoccur *wo, char *word) {
	wo->total += 1;

	int isnew = NEW;
	for (size_t i = 0; i<(wo->uniq); i++) {
		char *cur = wo_get(wo, i);
		if (strcmp(word, cur) == 0) {
			isnew = OLD;
		}
	}
	if (isnew == NEW) {
		wl_append(wo->words, str_dup(word));
		wo->uniq += 1;
	}
}

char *wo_get(wordoccur *wo, size_t index) {
	return wl_get(wo->words, index);
}
