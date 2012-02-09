CC = gcc
CCFLAGS = -Wall -g -std=c99

all: templates
	$(CC) $(CCFLAGS) -o tests int_arraylist.c tests.c

templates:
	./maketemplate arraylist.c int int
	./maketemplate arraylist.h int int
	./maketemplate arraylist.c str char\*
	./maketemplate arraylist.c str char\*

test:
	./tests
	
	

clean:
	rm -f int_arraylist.*
	rm -f str_arraylist.*
	rm -f tests
