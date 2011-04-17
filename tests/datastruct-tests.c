#include <stdio.h>
#include <assert.h>
#include "datastruct-tests.h"

void hashtable_debug(hashtable* ht) {
	hashtable_entry entry;
	int i;
	printf("Hashtable %p (%d / %d) {\n", ht, ht->size, ht->capacity);
	for(i = 0, entry = ht->body[i]; i < ht->size; entry = ht->body[++i]) {
	
		if (entry.key != NULL) {
			printf("   [\"%s\"] %p\n", entry.key, entry.value); 
		}
	}
	printf("}\n");
}

int main() {

	void* a = 0x500;
	void* b = 0x501;
	void* c = 0x502;
	void* d = 0x503;
	
	arraylist* l = arraylist_create();
	
	arraylist_debug(l);
	
	arraylist_add(l, a);
	arraylist_add(l, b);
	
	arraylist_debug(l);
	
	void* x = arraylist_pop(l);
	printf("%p\n", x);
	arraylist_add(l, c);
	
	arraylist* l2 = arraylist_create();
	arraylist_add(l2, b);
	arraylist_add(l2, d);
	arraylist_add(l2, a);
	arraylist_add(l2, b);
	
	arraylist_debug(l2);
	
	arraylist_insert(l2, 1, 0x504);
	
	arraylist_debug(l2);
	
	arraylist* copy = arraylist_slice(l2, 1, 3);
	
	arraylist_debug(copy);
	
	arraylist_clear(l2);
	
	arraylist_add(l2, 0x990);
	arraylist_add(l2, 0x991);
	arraylist_add(l2, 0x992);
	
	arraylist_splice(l2, l, 0);
	
	arraylist_debug(l2);
	

	/* 
	 * Hashtable tests
	 *
	 */
	
	
	hashtable* t = hashtable_create();
	assert(t->size == 0);	
	hashtable_set(t, "alpha", a);
	assert(t->size == 1);
	assert(hashtable_get(t, "alpha") == a);
	hashtable_remove(t, "alpha");
	assert(t->size == 0);
	assert(hashtable_get(t, "alpha") == NULL);
	hashtable_remove(t, "alpha");
	hashtable_set(t, "beta", b);
	hashtable_set(t, "beta", c);
	hashtable_set(t, "beta", a);
	hashtable_set(t, "beta", b);
	assert(t->size == 1);
	hashtable_set(t, "alpha", c);
	assert(hashtable_get(t, "beta") == b);
	assert(hashtable_get(t, "alpha") == c);
	
	hashtable_debug(t);
	
	hashtable_set(t, "gamma", b);
	hashtable_set(t, "delta", c);
	hashtable_set(t, "zeta", a);
	hashtable_set(t, "beta", b);
	
	hashtable_debug(t);
	
}
