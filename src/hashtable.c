#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "hashtable.h"

#if INTERFACE
struct hashtable_entry {
	char* key;
	void* value; 
};

struct hashtable {
	unsigned int size;
	unsigned int capacity;
	hashtable_entry* body;
};
#endif

#define HASHTABLE_INITIAL_CAPACITY 2

/* Compute the djb k=33 hash */
unsigned long hashtable_hash(char* str)
{
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;  /* hash * 33 + c */
	return hash;
}

unsigned int hashtable_find_slot(hashtable* t, char* key) {
	int index = hashtable_hash(key) % t->capacity;
	while (t->body[index].key != NULL && strcmp(t->body[index].key, key) != 0) {
		index = (index + 1) % t->capacity;
	}
	return index;
}

void* hashtable_get(hashtable* t, char* key) {
	int index = hashtable_find_slot(t, key);
	if (t->body[index].key != NULL) {
		return t->body[index].value;
	} else {
		return NULL;
	}
}

void* hashtable_set(hashtable* t, char* key, void* value) {
	int index = hashtable_find_slot(t, key);
	if (t->body[index].key != NULL) {
			/* Entry exists; update it. */
			t->body[index].value = value;
	} else {
			t->size ++;
			/* Create a new  entry */
			if ((float) t->size / t->capacity > 0.8) {
				/* Resize the hash table */
				hashtable_resize(t, t->capacity * 2);
				index = hashtable_find_slot(t, key);
			}
			t->body[index].key = key;
			t->body[index].value = value;
			
	}
}


void* hashtable_remove(hashtable* t, char* key) {
	int index = hashtable_find_slot(t, key);
	if (t->body[index].key != NULL) {
		t->body[index].key = NULL;
		t->body[index].value = NULL;
		t->size--;
	}
}


hashtable* hashtable_create() {
	hashtable* new_ht = malloc(sizeof(hashtable));
	new_ht->size = 0;
	new_ht->capacity = HASHTABLE_INITIAL_CAPACITY;
	new_ht->body = hashtable_body_allocate(new_ht->capacity);
	return new_ht;
}

hashtable_entry* hashtable_body_allocate(unsigned int capacity) {
	return (hashtable_entry*) calloc(capacity, sizeof(hashtable_entry));
}

/* Resize the allocated memory. Warning: clears the table of all entries. */
void hashtable_resize(hashtable* t, unsigned int capacity) {
	assert(capacity >= t->size);
	unsigned int old_capacity = t->capacity;
	hashtable_entry* old_body = t->body;
	t->body = hashtable_body_allocate(capacity);
	t->capacity = capacity;
	for (int i = 0; i < old_capacity; i++) {
		if (old_body[i].key != NULL) {
			hashtable_set(t, old_body[i].key, old_body[i].value);
		}
	}
}



