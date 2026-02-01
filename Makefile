SOURCES = arraylist.c hashtable.c tests.c

tests: $(SOURCES)
	gcc -fsanitize=address -g -o tests $(SOURCES)
	./tests

.PHONY: clean

clean:
	rm -f tests