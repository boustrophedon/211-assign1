#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "wc_util.h"

char* read_file(char fname[]) {
	FILE* fd = fopen(fname, "r");

	if (fd==NULL) {
		fprintf(stderr, "Couldn't open file.\n");
		return NULL;
	}

	if (fseek(fd, 0, SEEK_END)) {
		fprintf(stderr, "Couldn't seek to end of file.\n");
		return NULL;
	}

	size_t fsize = (size_t)ftell(fd);
	rewind(fd);
	

	char *fstring = malloc(sizeof(char)*(fsize+1));
	if (fstring == NULL) {
		fprintf(stderr, "Couldn't allocate memory for string.\n");
		return NULL;
	}

	fread(fstring, 1, fsize, fd);	
	fclose(fd);

	fstring[fsize] = '\0';

	return fstring;

}



/* I realized since there are literally functions isalnum and isalpha these aren't necessary. oh well. readability. */
int inword(char c) {
    if (isalnum(c)) {
        return 1;
    }
    else {
        return 0;
    }
}

/* same as inword, but doesn't accept a digit */
int inword_first(char c) {
    if (isalpha(c)) {
        return 1;
    }
    else {
        return 0;
    }
}

char *make_word(char *text, size_t first, size_t last) {
    size_t length = last-first+1;

    char *word = malloc( (length+1) * sizeof(char));
    strncpy(word, &(text[first]), length);
    word[length] = '\0';

    return word;
}

char *strdup(char *source) {
	size_t len = strlen(source);
	char *dest = malloc((len+1) * sizeof(char));

	memcpy(dest, source, len+1);

	return dest;
}

char *lowercase(char *source) {
	size_t len = strlen(source);
	char *dest = malloc((len+1) * sizeof(char));

	for (size_t i = 0; i < len; i++) {
		dest[i] = (char)tolower(source[i]);
	}
	dest[len] = '\0';
	return dest;
}

int strcmp_case_insensitive(char *a, char *b) {
	char *a_low = lowercase(a);
	char *b_low = lowercase(b);

	int ret = strcmp(a_low, b_low);

	free(a_low);free(b_low);

	return ret;
}

/* only for use with qsort */
int compare_strings_lower(const void *a, const void *b) {
	char *astr = *(char **)a;
	char *bstr = *(char **)b;

	char *a_low = lowercase(astr);
	char *b_low = lowercase(bstr);

	int ret = strcmp(a_low, b_low);

	free(a_low); free(b_low);

	return ret;
}

