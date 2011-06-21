#include <stdio.h>
#include <assert.h>
#include "tests.h"
/**
 * These are tests for arraylist.c and hastable.c
 *
 * The tests are currently a work in progress. Their aim is to cover
 * all of arraylist and hashtable functionality.
 */


int main()
{
	/*
	 * Make a few dummy pointers as values for testing.
	 * These are never dereferenced.
	 */
	void* a = (void*)0x500;
	void* b = (void*)0x501;
	void* c = (void*)0x502;
	void* d = (void*)0x503;
	void* e = (void*)0x504;
	void* f = (void*)0x505;




	/*
	 * Arraylist tests
	 */
	printf("Running arraylist.c tests.\n");

	arraylist* l = arraylist_create();

	assert(l->size == 0);

	arraylist_add(l, a);
	arraylist_add(l, b);

	assert(l->size == 2);
	assert(arraylist_get(l, 0) == a);
	assert(arraylist_get(l, 1) == b);

	arraylist_add(l, c);
	arraylist_add(l, d);

	assert(l->size == 4);
	assert(arraylist_get(l, 3) == d);
	assert(arraylist_get(l, 2) == c);
	assert(arraylist_pop(l) == d);
	assert(arraylist_pop(l) == c);
	assert(l->size == 2);

	//arraylist_debug(l);

	arraylist_add(l, e);
	arraylist_add(l, f);
	arraylist_insert(l, 2, c);


	//arraylist_debug(l);

	assert(l->size == 5);
	assert(arraylist_get(l, 0) == a);
	assert(arraylist_get(l, 1) == b);
	assert(arraylist_get(l, 2) == c);
	assert(arraylist_get(l, 3) == e);
	assert(arraylist_get(l, 4) == f);

	arraylist_remove(l, 1);
	assert(l->size == 4);
	assert(arraylist_get(l, 0) == a);
	assert(arraylist_get(l, 1) == c);
	assert(arraylist_get(l, 2) == e);

	arraylist* slice = arraylist_slice(l, 1, 2);
	assert(slice->size == 2);
	assert(arraylist_get(slice, 0) == c);
	assert(arraylist_get(slice, 1) == e);

	arraylist* copy = arraylist_copy(l);
	assert(copy->size == l->size);
	int i;
	void* v;
	arraylist_iterate(copy, i, v) {
		assert(v == arraylist_get(l, i));
	}

	arraylist_clear(l);
	assert(l->size == 0);
	arraylist_iterate(l, i, v) {
		assert(0); // Iterating over an empty list should never run.
	}

	arraylist_destroy(l);
	arraylist_destroy(slice);
	arraylist_destroy(copy);



	/*
	 * Hashtable tests
	 */

	printf("Running hashtable.c tests.\n");

	hashtable* t = hashtable_create();

	assert(t->size == 0);

	hashtable_set(t, "alpha", a);

	assert(t->size == 1);
	assert(hashtable_get(t, "alpha") == a);
	assert(hashtable_get(t, "beta") == NULL);

	hashtable_remove(t, "alpha");

	assert(t->size == 0);
	assert(hashtable_get(t, "alpha") == NULL);

	hashtable_set(t, "beta", b);

	assert(t->size == 1);
	assert(hashtable_get(t, "beta") == b);

	hashtable_set(t, "beta", c);

	assert(t->size == 1);
	assert(hashtable_get(t, "beta") == c);

	hashtable_destroy(t);

	printf("All tests completed.\n");
}
