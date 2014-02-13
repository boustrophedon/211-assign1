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

void ol_add_words(occurlist *ol, wordlist *wl) {
	wordoccur *cur_wo = NULL;

	int state = NEW;

	/* i feel like this loop is a bit too complicated */
	for (size_t i = 1; i < wl_size(wl); i++) {
		char *word = wl_get(wl, i);
		if (state == OLD) {
			if (strcmp_case_insensitive(word, cur_wo->lower) != 0) {
				state = NEW;
			}
			else {
				wo_update(cur_wo, word);
			}
		}
		if (state == NEW) {
			cur_wo = wo_create(word);
			(ol->wo_arr)[ol->size] = cur_wo;
			ol->size += 1;

			state = OLD;
		}
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
	wl_append(new_wo->words, strdup(word));

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
	for (size_t i = 0; i<(wo->uniq); i++) {
		char *cur = wo_get(wo, i);
		if (strcmp(word, cur) != 0) {
			wl_append(wo->words, strdup(word));
			wo->uniq += 1;
			return;
		}
	}
}

char *wo_get(wordoccur *wo, size_t index) {
	return wl_get(wo->words, index);
}
