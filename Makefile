CC=clang
CFLAGS=-g -std=c99 -pedantic -Wall -Werror -Weverything
LDFLAGS=-g

all: wordstat

wordstat: wordstat.o wordlist.o wc_util.o
		$(CC) $(LDFLAGS) wordstat.o wordlist.o wc_util.o -o wordstat

wordstat.o: wordstat.c 
		$(CC) $(CFLAGS) -c wordstat.c

wordlist.o: wordlist.c
		$(CC) $(CFLAGS) -c wordlist.c

wc_util.o: wc_util.c
		$(CC) $(CFLAGS) -c wc_util.c


clean:
		rm wordstat *o

