#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* read_file(char fname[]) {
	FILE* fd;
	size_t fsize;
	char* fstring;

	fd = fopen(fname, "r");

	if (fd==NULL) {
		fprintf(stderr, "Couldn't open file.\n");
		return NULL;
	}

	if (fseek(fd, 0, SEEK_END)) {
		fprintf(stderr, "Couldn't seek to end of file.\n");
		return NULL;
	}

	fsize = ftell(fd);

	fseek(fd, 0, SEEK_SET);

	fstring = malloc(sizeof(char)*fsize);
	if (fstring == NULL) {
		fprintf(stderr, "Couldn't allocate memory for string.\n");
		return NULL;
	}

	fread(fstring, 1, fsize, fd);	
	fclose(fd);

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
    int length = last-first+1;

    char *word = malloc( (length+1) * sizeof(char));
    strncpy(word, &(text[first]), length);
    word[length] = '\0';

    return word;
}



char *lowercase(char *source) {
	size_t len = strlen(source);
	char *dest = malloc(len * sizeof(char));

	for (int i = 0; i < len; i++) {
		dest[i] = tolower(source[i]);
	}
	return dest;
}

int compare_strings_lower(const void *a, const void *b) {
	char *astr = *(char **)a;
	char *bstr = *(char **)b;

	return strcmp(lowercase(astr), lowercase(bstr));
}

