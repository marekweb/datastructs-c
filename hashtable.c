#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "ht.h"

#if INTERFACE
struct alht_ht_entry {
	char* key;
	void* value; 
};

struct alht_ht {
	unsigned int size;
	unsigned int capacity;
	alht_ht_entry* body;
};
#endif

#define ALHT_HT_CAPACITY 2

/* Compute the djb k=33 hash */
unsigned long alht_ht_hash(char* str)
{
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;  /* hash * 33 + c */
	return hash;
}

unsigned int alht_ht_find_slot(alht_ht* t, char* key) {
	int index = alht_ht_hash(key) % t->capacity;
	while (t->body[index].key != NULL && strcmp(t->body[index].key, key) != 0) {
		index = (index + 1) % t->capacity;
	}
	return index;
}

void* alht_ht_get(alht_ht* t, char* key) {
	int index = alht_ht_find_slot(t, key);
	if (t->body[index].key != NULL) {
		return t->body[index].value;
	} else {
		return NULL;
	}
}

void* alht_ht_set(alht_ht* t, char* key, void* value) {
	int index = alht_ht_find_slot(t, key);
	if (t->body[index].key != NULL) {
			/* Entry exists; update it. */
			t->body[index].value = value;
	} else {
			t->size ++;
			/* Create a new  entry */
			if ((float) t->size / t->capacity > 0.8) {
				/* Resize the hash table */
				alht_ht_resize(t, t->capacity * 2);
				index = alht_ht_find_slot(t, key);
			}
			t->body[index].key = key;
			t->body[index].value = value;
			
	}
}


void* alht_ht_remove(alht_ht* t, char* key) {
	int index = alht_ht_find_slot(t, key);
	if (t->body[index].key != NULL) {
		t->body[index].key = NULL;
		t->body[index].value = NULL;
		t->size--;
	}
}

alht_ht* alht_ht_create() {
	alht_ht* new_ht = malloc(sizeof(alht_ht));
	new_ht->size = 0;
	new_ht->capacity = ALHT_HT_CAPACITY;
	new_ht->body = alht_ht_body_allocate(new_ht->capacity);
	return new_ht;
}

alht_ht_entry* alht_ht_body_allocate(unsigned int capacity) {
	return (alht_ht_entry*) calloc(capacity, sizeof(alht_ht_entry));
}

/* Resize the allocated memory. Warning: clears the table of all entries. */
void alht_ht_resize(alht_ht* t, unsigned int capacity) {
	assert(capacity >= t->size);
	unsigned int old_capacity = t->capacity;
	alht_ht_entry* old_body = t->body;
	t->body = alht_ht_body_allocate(capacity);
	t->capacity = capacity;
	for (int i = 0; i < old_capacity; i++) {
		if (old_body[i].key != NULL) {
			alht_ht_set(t, old_body[i].key, old_body[i].value);
		}
	}
}



