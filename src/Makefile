CC = clang
CCFLAGS = -Wall -g -std=c99

all: templates
	$(CC) $(CCFLAGS) -o tests int_arraylist.c int_hashtable.c tests.c

templates:
	./maketemplate arraylist.c int int
	./maketemplate arraylist.h int int
	./maketemplate hashtable.c int int
	./maketemplate hashtable.h int int 

test:
	./tests
	
	

clean:
	rm -f int_arraylist.*
	rm -f int_hashtable.*
	rm -f tests
