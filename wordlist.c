#include <stdio.h>
#include <stdlib.h>

#include "wordlist.h"

wordlist *wl_create() {
    wordlist *new_wl = malloc(sizeof(wordlist));
    
    new_wl->array_size = INITIAL_SIZE;
    new_wl->num_elements = 0;

    new_wl->arr = malloc(new_wl->array_size * sizeof(char*));

    return new_wl;
}

/* returns 0 if grow succeeds, -1 if fails to allocate new memory */
int wl_grow(wordlist *wl) {
    char **newarr = realloc(wl->arr, 2*(wl->array_size) * sizeof(char*));

    if (newarr == NULL) {
        fprintf(stderr, "Couldn't allocate enough memory.\n"); /* error message shouldn't really be here but whatever. */
        return -1;
    }
    else {
        wl->arr = newarr;
		wl->array_size = 2*(wl->array_size);
        return 0;
    }
}

/* returns 0 if append succeeds, -1 if fails */
int wl_append(wordlist *wl, char *word) {
    if (wl->num_elements < (wl->array_size - 1)) {
        wl->arr[wl->num_elements] = word;
        wl->num_elements += 1;

        return 0;
    }

    else {
        if (!wl_grow(wl)) { /* can grow list; have enough memory */
            return wl_append(wl, word);
        }
        else {
			fprintf(stderr, "Append failed.\n");
            return -1;
        }
    }
}

char *wl_get(wordlist *wl, size_t index) {

    if (index < wl_size(wl)) {
        return wl->arr[index];
    }
    else {
        return NULL;
    }

}

int wl_set(wordlist *wl, size_t index, char *word) {
    /* STUBBED until needed */
    return 0;

}


size_t wl_size(wordlist *wl) {
    return wl->num_elements;
}
