#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wordstat.h"
#include "wordlist.h"
#include "occurlist.h"
#include "wc_util.h"

#define IN 1
#define OUT 0

/* this essentially does part of processStr from the problem description pdf */
void parse_words(char *text, wordlist *wl) { 
	int state = OUT;

	size_t pos = 0;
	size_t first = pos;
	size_t last = pos;

	char cur = text[0];

	while (cur != '\0') {
		if (state == OUT) {
			if (inword_first(cur)) {
				state = IN;
				first = pos;
				last = pos;
			}
		}
		else { /* state == IN */
			if (inword(cur)) {
				last++;
			}
			else {
				wl_append(wl, make_word(text, first, last));
				state = OUT;
			}
		}

		pos++;
		cur = text[pos];
	}

	/* make one more string depending on whether cur == '\0' and we were in a word when we got there */
	if ((cur == '\0') && (state == IN)) {
		wl_append(wl, make_word(text, first, last));
	}
}

int main(int argc, char *argv[]) {
	wordlist *wl = wl_create();

	char *arg1 = argv[1];
	if ((argc == 1) || (strcmp(arg1, "-h") == 0)) {
		printf("help text goes here\n");
		return 0;
	}
	
	char *text = read_file(arg1);
	if (text == NULL) {
		fprintf(stderr, "Exiting.\n");
		return -1;
	}

	parse_words(text, wl);

	wl_sort(wl);

	for (size_t i = 0; i < wl_size(wl); i++) {
		printf("%s\n", wl_get(wl, i));
	}


	occurlist *ol = ol_create(wl);

	ol_print(ol); /* printResult in the pdf */

	/* cleanup */
	wl_delete(wl);
	ol_delete(ol);
	free(text);
	
    return 0;
}
