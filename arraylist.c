/**
 * Arraylist implementation
 * (c) 2011 @marekweb
 *
 * Uses dynamic extensible arrays.
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "arraylist.h"

/*
 * Interface section used for `makeheaders`.
 */
#if INTERFACE

struct arraylist {
	unsigned int size; // Count of items currently in list
	unsigned int capacity; // Allocated memory size, in items
	void** body; // Pointer to allocated memory for items (of size capacity * sizeof(void*))
};

/**
 * Iterates over a list, using the provided `unsigned int index` and `void* item`
 * variables as containers.
 */
#define arraylist_iterate(l, index, item) \
	for (index = 0, item = l->body[0]; index < l->size; item = l->body[++index])

#endif

// Initial capacity of the arraylist
#define ARRAYLIST_INITIAL_CAPACITY 4

/**
 * Macro to shift a section of memory by an offset, used when inserting or removing items.
 */
#define arraylist_memshift(s, offset, length) memmove((s) + (offset), (s), (length)* sizeof(s));

/**
 * Create a new, empty arraylist.
 */
arraylist* arraylist_create()
{
	arraylist* new_list = malloc(sizeof(arraylist));
	new_list->size = 0;
	// Allocate the array
	new_list->body = malloc(sizeof(void*) * ARRAYLIST_INITIAL_CAPACITY);
	assert(new_list->body);
	new_list->capacity = ARRAYLIST_INITIAL_CAPACITY;
	return new_list;
}

/**
 * Allocate sufficient array capacity for at least `size` elements.
 */
void arraylist_allocate(arraylist* l, unsigned int size)
{
	assert(size > 0);
	if (size > l->capacity) {
		unsigned int new_capacity = l->capacity;
		while (new_capacity < size) {
			new_capacity *= 2;
		}
		l->body = realloc(l->body, sizeof(void*) * new_capacity);
		assert(l->body);
		l->capacity = new_capacity;
	}
}

/** 
 * Return the number of items contained in the list.
 */
extern inline unsigned int arraylist_size(arraylist*l) {
	return l->size;
}

/**
 * Add item at the end of the list.
 */
void arraylist_add(arraylist* l, void* item)
{
	arraylist_allocate(l, l->size + 1);
	l->body[l->size++] = item;
}

/**
 * Pop (remove and return) an item off the end of the list.
 */
void* arraylist_pop(arraylist* l)
{
	assert(l->size > 0);
	return l->body[--l->size];
}

/**
 * Return item located at index.
 */
void* arraylist_get(arraylist* l, unsigned int index)
{
	assert(index < l->size);
	return l->body[index];
}

/**
 * Replace item at index with given value.
 */
void arraylist_set(arraylist* l, unsigned int index, void* value)
{
	assert(index < l->size);
	l->body[index] = value;
}

/**
 * Insert item at index, shifting the following items by one spot.
 */
void arraylist_insert(arraylist* l, unsigned int index, void* value)
{
	// Reallocate, if needed
	arraylist_allocate(l, l->size + 1);

	// Move data to create a spot for the new value
	arraylist_memshift(l->body + index, 1, l->size - index);
	l->body[index] = value;
	l->size++;
}

/**
 * Remove the item at index, shifting the following items back by one spot.
 */
void* arraylist_remove(arraylist* l, unsigned int index)
{
	void* value = l->body[index];
	arraylist_memshift(l->body + index + 1, -1, l->size - index);
	l->size--;
	return value;
}

/**
 * Clear list of all items.
 */
void arraylist_clear(arraylist* l)
{
	l->size = 0;
}

/**
 * Return a slice of the list (of given length starting at index) as a new arraylist.
 */
arraylist* arraylist_slice(arraylist* l, unsigned int index, unsigned int length)
{
	assert(index + length <= l->size);
	arraylist* new_list = arraylist_create();
	arraylist_allocate(new_list, length);
	memmove(new_list->body, l->body + index, length * sizeof(void*));
	new_list->size = length;
	return new_list;
}

/**
 * Return a slice of the list (from index to the end) as a new arraylist.
 */
arraylist* arraylist_slice_end(arraylist* l, unsigned int index)
{
	return arraylist_slice(l, index, l->size - index);
}

/**
 * Return a copy of the arraylist.
 */
arraylist* arraylist_copy(arraylist* l)
{
	return arraylist_slice_end(l, 0);
}

/**
 * Append a list onto another, in-place.
 */
void arraylist_join(arraylist* l, arraylist* source)
{
	arraylist_splice(l, source, l->size);
}

/**
 * Insert a list into another at the given index, in-place.
 */
void arraylist_splice(arraylist* l, arraylist* source, unsigned int index)
{
	// Reallocate, if needed
	arraylist_allocate(l, l->size + source->size);

	// Move data to the right
	arraylist_memshift(l->body + index, source->size, l->size - index);

	// Copy the data over
	memmove(l->body + index, source->body, source->size * sizeof(void*));
	l->size += source->size;
}

void arraylist_destroy(arraylist* l)
{
	free(l->body);
	free(l);
}

