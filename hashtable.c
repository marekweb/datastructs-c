/**
 * Generic Hashtable implementation.
 * (c) 2011-2012 Marek Zaluski 
 *
 * Instantiate the template with maketemplate script.
 *
 * Uses dynamic addressing with linear probing.
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "TPL_N_hashtable.h"

/*
 * Interface section used for `makeheaders`.
 */

#ifndef HASHTABLE_INITIAL_CAPACITY
#define HASHTABLE_INITIAL_CAPACITY 8
#endif
/**
 * Compute the hash value for the given string.
 * Implements the djb k=33 hash function.
 */
unsigned long TPL_N_hashtable_hash(char* str)
{
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;  /* hash * 33 + c */
	return hash;
}

/**
 * Find an available slot for the given key, using linear probing.
 */
unsigned int TPL_N_hashtable_find_slot(TPL_N_hashtable* t, char* key)
{
	int index = TPL_N_hashtable_hash(key) % t->capacity;
	while (t->body[index].key != NULL && strcmp(t->body[index].key, key) != 0) {
		index = (index + 1) % t->capacity;
	}
	return index;
}

/**
 * Get the value associated with the given key, placing it into ptr; return 1 on success, or 0 
 * if the key was not found.:
 */

int TPL_N_hashtable_get(TPL_N_hashtable* t, char* key, TPL_T* ptr)
{
	int index = TPL_N_hashtable_find_slot(t, key);
	if (t->body[index].key != NULL) {
		*ptr = t->body[index].value;
		return 1;
	}
	return 0;
}

/**
 * Assign a value to the given key in the table.
 */
void TPL_N_hashtable_set(TPL_N_hashtable* t, char* key, TPL_T  value)
{
	int index = TPL_N_hashtable_find_slot(t, key);
	if (t->body[index].key != NULL) {
		/* Entry exists; update it. */
		t->body[index].value = value;
	} else {
		t->size++;
		/* Create a new  entry */
		if ((float)t->size / t->capacity > 0.8) {
			/* Resize the hash table */
			TPL_N_hashtable_resize(t, t->capacity * 2);
			index = TPL_N_hashtable_find_slot(t, key);
		}
		t->body[index].key = key;
		t->body[index].value = value;
	}
}

/**
 * Remove a key from the table
 */
void TPL_N_hashtable_remove(TPL_N_hashtable* t, char* key)
{
	int index = TPL_N_hashtable_find_slot(t, key);
	if (t->body[index].key != NULL) {
		t->body[index].key = NULL;
		t->size--;
	}
}

/**
 * Create a new, empty TPL_N_hashtable
 */
TPL_N_hashtable* TPL_N_hashtable_create()
{
	TPL_N_hashtable* new_ht = malloc(sizeof(TPL_N_hashtable));
	new_ht->size = 0;
	new_ht->capacity = HASHTABLE_INITIAL_CAPACITY;
	new_ht->body = TPL_N_hashtable_body_allocate(new_ht->capacity);
	return new_ht;
}

#if 0
/**
 * Adds all items from another table.
 */
TPL_N_hashtable* TPL_N_hashtable_merge(TPL_N_hashtable* ht, TPL_N_hashtable* other)
{
}
#endif

/**
 * Allocate a new memory block with the given capacity.
 */
TPL_N_hashtable_entry* TPL_N_hashtable_body_allocate(unsigned int capacity)
{
	return (TPL_N_hashtable_entry*)calloc(capacity, sizeof(TPL_N_hashtable_entry));
}

/**
 * Resize the allocated memory.
 */
void TPL_N_hashtable_resize(TPL_N_hashtable* t, unsigned int capacity)
{
	assert(capacity >= t->size);
	unsigned int old_capacity = t->capacity;
	TPL_N_hashtable_entry* old_body = t->body;
	t->body = TPL_N_hashtable_body_allocate(capacity);
	t->capacity = capacity;
	for (int i = 0; i < old_capacity; i++) {
		if (old_body[i].key != NULL) {
			TPL_N_hashtable_set(t, old_body[i].key, old_body[i].value);
		}
	}
}

/**
 * Destroy the table and deallocate it from memory. This does not deallocate the contained items.
 */
void TPL_N_hashtable_destroy(TPL_N_hashtable* t)
{
	free(t->body);
	free(t);
}

