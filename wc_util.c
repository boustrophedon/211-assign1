#include <stdio.h>
#include <stdlib.h>

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
