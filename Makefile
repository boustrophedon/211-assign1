CC=clang
CFLAGS=-g -std=c99 -pedantic -Wall -Werror
LDFLAGS=-g

all: wordstat

wordstat: wordcount.o wordlist.o wc_util.o
		$(CC) $(LDFLAGS) wordcount.o wordlist.o wc_util.o -o wordstat

wordcount.o: wordcount.c wordcount.h wordlist.h wc_util.h
		$(CC) $(CFLAGS) -c wordcount.c

wordlist.o: wordlist.c wordlist.h
		$(CC) $(CFLAGS) -c wordlist.c

wc_util.o: wc_util.c wc_util.h
		$(CC) $(CFLAGS) -c wc_util.c


clean:
		rm wordstat *o

