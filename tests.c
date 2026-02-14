#include <stdio.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include "arraylist.h"
#include "hashtable.h"
/**
 * These are tests for arraylist.c and hastable.c
 *
 * The tests are currently a work in progress. Their aim is to cover
 * all of arraylist and hashtable functionality.
 */

void arraylist_debug(arraylist* l) {
	int i;
	void* v;
	arraylist_iterate(l, i, v) {
		printf("[%i] = %p\n", i, v);

	}
}

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

	arraylist_add(l, e);
	arraylist_add(l, f);
	arraylist_insert(l, 2, c);

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

	arraylist_debug(copy);

	arraylist_clear(l);
	assert(l->size == 0);
	arraylist_iterate(l, i, v) {
		assert(0); // Iterating over an empty list should never run.
	}

	arraylist_destroy(l);
	arraylist_destroy(slice);
	arraylist_destroy(copy);

	/*
	 * Test: arraylist_remove should not read beyond array bounds.
	 * When size == capacity and we remove from the middle, the memshift
	 * should not access memory beyond the last valid element.
	 */
	arraylist* l2 = arraylist_create();
	arraylist_add(l2, a);
	arraylist_add(l2, b);
	arraylist_add(l2, c);
	arraylist_add(l2, d);
	// Now size == capacity == 4

	// Remove from index 1: should shift elements at indices 2,3 left
	// Bug: current code tries to also read index 4 (out of bounds)
	void* removed = arraylist_remove(l2, 1);
	assert(removed == b);
	assert(l2->size == 3);
	assert(arraylist_get(l2, 0) == a);
	assert(arraylist_get(l2, 1) == c);
	assert(arraylist_get(l2, 2) == d);

	// Remove from last valid index when at capacity boundary
	arraylist_add(l2, e);  // size == capacity == 4 again
	removed = arraylist_remove(l2, 2);
	assert(removed == d);
	assert(l2->size == 3);
	assert(arraylist_get(l2, 0) == a);
	assert(arraylist_get(l2, 1) == c);
	assert(arraylist_get(l2, 2) == e);

	arraylist_destroy(l2);

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

	/*
	 * Test: hashtable_remove should not break linear probing chains.
	 * Keys "ab" and "ba" both hash to the same slot (0) with capacity 4.
	 * Removing "ab" should not prevent finding "ba".
	 */
	hashtable* t2 = hashtable_create();

	hashtable_set(t2, "ab", a);  // Goes to slot 0
	hashtable_set(t2, "ba", b);  // Collision, goes to slot 1

	// Both should be findable
	assert(hashtable_get(t2, "ab") == a);
	assert(hashtable_get(t2, "ba") == b);

	// Remove the first one in the chain
	hashtable_remove(t2, "ab");

	// "ba" should still be findable (this will fail with the current bug)
	assert(hashtable_get(t2, "ba") == b);

	// Re-insert "ab" with a different value
	hashtable_set(t2, "ab", c);
	assert(hashtable_get(t2, "ab") == c);
	assert(hashtable_get(t2, "ba") == b);  // "ba" should still work
	assert(t2->size == 2);

	hashtable_destroy(t2);

	/*
	 * Test: hashtable_resize should preserve accurate size count.
	 * Insert 4 unique entries to trigger resize (>80% load).
	 */
	hashtable* t3 = hashtable_create();
	assert(t3->size == 0);

	hashtable_set(t3, "k1", a);
	hashtable_set(t3, "k2", b);
	hashtable_set(t3, "k3", c);
	hashtable_set(t3, "k4", d);

	assert(t3->size == 4);
	assert(hashtable_get(t3, "k1") == a);
	assert(hashtable_get(t3, "k4") == d);

	hashtable_destroy(t3);

	/*
	 * Test: inserting into a table full of tombstones should not infinite loop.
	 * Keys "ab", "ba", "cd", "dc", "ef" all hash to slot 0 with capacity 4.
	 */
	signal(SIGALRM, SIG_DFL);
	alarm(2);

	hashtable* t4 = hashtable_create();
	hashtable_set(t4, "ab", a);  // slot 0
	hashtable_set(t4, "ba", b);  // slot 1
	hashtable_set(t4, "cd", c);  // slot 2

	hashtable_remove(t4, "ab");  // tombstone at 0
	hashtable_remove(t4, "ba");  // tombstone at 1
	hashtable_remove(t4, "cd");  // tombstone at 2

	// "dc" hashes to slot 0, probes past tombstones, lands on slot 3 (NULL)
	hashtable_set(t4, "dc", d);

	// "ef" hashes to slot 0: all 4 slots are non-NULL (3 tombstones + "dc")
	// Bug: hashtable_find_slot loops forever here
	hashtable_set(t4, "ef", e);

	assert(t4->size == 2);
	assert(hashtable_get(t4, "dc") == d);
	assert(hashtable_get(t4, "ef") == e);

	alarm(0);
	hashtable_destroy(t4);

	printf("All tests completed.\n");
}
