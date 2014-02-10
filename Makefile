CC=clang
CFLAGS=-g -std=c99 -pedantic -Wall -Werror
LDFLAGS=-g

all: wordcount

wordcount: wordcount.o wordlist.o
		$(CC) $(LDFLAGS) wordcount.o wordlist.o -o wordcount

wordcount.o: wordcount.c wordcount.h wordlist.h
		$(CC) $(CFLAGS) -c wordcount.c

wordlist.o: wordlist.c wordlist.h
		$(CC) $(CFLAGS) -c wordlist.c

clean:
		rm wordcount *o

