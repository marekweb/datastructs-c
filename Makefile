tests: arraylist.c hashtable.c tests.c
	gcc -o tests arraylist.c hashtable.c tests.c && ./tests

.PHONY: clean

clean:
	rm tests