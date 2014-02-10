#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wordlist.h"
#include "wc_util.h"

int main(int argc, char *argv[]) {
	wordlist *wl = wl_create();
	printf("%zd\n", wl_size(wl));

	char *arg1 = argv[1];
	if ((arg1 == NULL) || (strcmp(arg1, "-h") == 0)) {
		printf("help text goes here\n");
		return 0;
	}
	
	char *text = read_file(arg1);
	if (text == NULL) {
		fprintf(stderr, "Exiting.\n");
	}

    return 0;
}
