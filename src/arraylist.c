/**
 * Array List
 * (c) 2011 @marekweb
 */

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "arraylist.h"

#if INTERFACE
/* Iterator macro
 * Usage:
 *
 * int index;
 * void* item;
 * arraylist_iterate(list, index, item) {
 * 		// Use index and item
 * }
 */
#define arraylist_iterate(l, index, item) \
	for (index = 0, item = l->body[0]; index < l->size; item = l->body[++index])
struct arraylist {
	unsigned int size;
	unsigned int capacity;
	void** body;
};
#endif

// Initial capacity of the arraylist
#define ARRAYLIST_INITIAL_CAPACITY 4

arraylist* arraylist_create() {
	arraylist* new_list = malloc(sizeof(arraylist));
	new_list->size = 0;
	// Allocate the array
	new_list->body = malloc(sizeof(void*) * ARRAYLIST_INITIAL_CAPACITY);
	assert(new_list->body);
	new_list->capacity = ARRAYLIST_INITIAL_CAPACITY;
	return new_list;
}

void arraylist_allocate(arraylist* l, unsigned int size) {
	assert(size > 0);
	if (size > l->capacity) {
		
		unsigned int new_capacity = l->capacity;
		while (new_capacity < size) {
			new_capacity *= 2;
		}
	//	printf("Reallocating %p from %zu to %zu to accomodate %zu items.\n", l, l->capacity, new_capacity, size);
		l->body = realloc(l->body, sizeof(void*) * new_capacity);
		assert(l->body);
		l->capacity = new_capacity;
	}
}


void arraylist_add(arraylist* l, void* item) {
	arraylist_allocate(l, l->size+1);
	l->body[l->size++] = item;
}

void* arraylist_pop(arraylist* l) {
	assert(l->size > 0);
	return l->body[--l->size];
}

void* arraylist_get(arraylist* l, unsigned int index) {
	assert(index < l->size);
	return l->body[index];
}

void arraylist_set(arraylist* l, unsigned int index, void* value) {
	assert(index < l->size);
	l->body[index] = value;
}

void arraylist_insert(arraylist* l, unsigned int index, void* value) {
	// Reallocate, if needed
	arraylist_allocate(l, l->size+1);
	// Move data to create a spot for the new value
	memmove(l->body + index + 1, l->body + index, l->size - index);

	l->body[index] = value;
	l->size++;
}

void* arraylist_remove(arraylist* l, unsigned int index) {
	void* value = l->body[index];
	memmove(l->body + index, l->body + index + 1, l->size - index);
	l->size--;
	return value;
}

void* arraylist_clear(arraylist* l) {
	l->size = 0;
}


arraylist* arraylist_slice(arraylist* l, unsigned int index, unsigned int length) {
	assert(index + length <= l->size);
	arraylist* new_list = arraylist_create();
	arraylist_allocate(new_list, length);
	memmove(new_list->body, l->body + index, length * sizeof(void*));
	new_list->size = length;
	return new_list;
}

arraylist* arraylist_slice_end(arraylist* l, unsigned int index) {
	return arraylist_slice(l, index, l->size - index);
}

arraylist* arraylist_copy(arraylist* l) {
	return arraylist_slice_end(l, 0);
}

void* arraylist_join(arraylist* l, arraylist* source) {
	arraylist_splice(l, source, l->size);
}

void* arraylist_splice(arraylist* l, arraylist* source, unsigned int index) {
	// Reallocate, if needed
	arraylist_allocate(l, l->size + source->size);
	// Move data to the right
	memmove(l->body + index + source->size, l->body + index, (l->size - index) * sizeof(void*));
	// Copy the data over
	memmove(l->body + index, source->body, source->size * sizeof(void*)); 
	l->size += source->size;
}

#include <stdio.h>
void* arraylist_debug(arraylist* l) {
	printf("Arraylist %p (%d / %d) {\n", l, l->size, l->capacity);
	int index;
	void* item;
	arraylist_iterate(l, index, item) {
		printf("   [%d] %p\n", index, item);
	}
	printf("}\n");
}

