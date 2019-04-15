CC=gcc
CFLAGS=-c -Wall -g

all: cache

p1: cache.o
	$(CC) cache.o -o cache

cache.o: cache.c
	$(CC) $(CFLAGS) cache.c

clean:
	/bin/rm -f cache *.o *.gz

run:
	./cache

tarball:
	tar -cvzf cache.tar.gz *
