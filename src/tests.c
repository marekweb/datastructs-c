#include <stdio.h>
#include <assert.h>
#include "int_arraylist.h"

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
	int a = 435;
	int b = 234;
	int c = 12;
	int d = 9510;
	int e = 12455;
	int f = 551;




	/*
	 * Arraylist tests
	 */
	printf("Running int_arraylist.c tests.\n");

	int_arraylist* l = int_arraylist_create();

	assert(l->size == 0);

	int_arraylist_add(l, a);
	int_arraylist_add(l, b);

	assert(l->size == 2);
	assert(int_arraylist_get(l, 0) == a);
	assert(int_arraylist_get(l, 1) == b);

	int_arraylist_add(l, c);
	int_arraylist_add(l, d);

	assert(l->size == 4);
	assert(int_arraylist_get(l, 3) == d);
	assert(int_arraylist_get(l, 2) == c);
	assert(int_arraylist_pop(l) == d);
	assert(int_arraylist_pop(l) == c);
	assert(l->size == 2);

	//arraylist_debug(l);

	int_arraylist_add(l, e);
	int_arraylist_add(l, f);
	int_arraylist_insert(l, 2, c);


	//arraylist_debug(l);

	assert(l->size == 5);
	assert(int_arraylist_get(l, 0) == a);
	assert(int_arraylist_get(l, 1) == b);
	assert(int_arraylist_get(l, 2) == c);
	assert(int_arraylist_get(l, 3) == e);
	assert(int_arraylist_get(l, 4) == f);

	int_arraylist_remove(l, 1);
	assert(l->size == 4);
	assert(int_arraylist_get(l, 0) == a);
	assert(int_arraylist_get(l, 1) == c);
	assert(int_arraylist_get(l, 2) == e);

	int_arraylist* slice = int_arraylist_slice(l, 1, 2);
	assert(slice->size == 2);
	assert(int_arraylist_get(slice, 0) == c);
	assert(int_arraylist_get(slice, 1) == e);

	int_arraylist* copy = int_arraylist_copy(l);
	assert(copy->size == l->size);
	int i;
	int v;
	int_arraylist_iterate(copy, i, v) {
		assert(v == int_arraylist_get(l, i));
	}

	int_arraylist_clear(l);
	assert(l->size == 0);
	int_arraylist_iterate(l, i, v) {
		assert(0); // Iterating over an empty list should never run.
	}

	int_arraylist_destroy(l);
	int_arraylist_destroy(slice);
	int_arraylist_destroy(copy);



	/*
	 * Hashtable tests
	 */
#if 0
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
#endif
}
