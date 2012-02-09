CC = gcc 
CCFLAGS = -Wall -g -std=c99

all: templates
	$(CC) $(CCFLAGS) -o tests int_arraylist.c int_hashtable.c tests.c

templates:
	./maketemplate arraylist int int
	./maketemplate hashtable int int

test: all
	./tests
	
clean:
	rm -f int_arraylist.*
	rm -f int_hashtable.*
	rm -f tests
