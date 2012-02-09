/**
 * Arraylist implementation
 * (c) 2011 @marekweb
 *
 * Uses dynamic extensible arrays.
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "TPL_N_arraylist.h"

// Initial capacity of the TPL_N_arraylist
#define ARRAYLIST_INITIAL_CAPACITY 4


#define memshift(s, offset, length) memmove((s) + (offset), (s), (length) * sizeof(s));

/**
 * Create a new, empty TPL_N_arraylist.
 */
TPL_N_arraylist * TPL_N_arraylist_create()
{
	TPL_N_arraylist * new_list = malloc(sizeof(TPL_N_arraylist));
	new_list->size = 0;
	// Allocate the array
	new_list->body = malloc(sizeof(TPL_T) * ARRAYLIST_INITIAL_CAPACITY);
	assert(new_list->body);
	new_list->capacity = ARRAYLIST_INITIAL_CAPACITY;
	return new_list;
}

/**
 * Allocate sufficient array capacity for at least `size` elements.
 */
void TPL_N_arraylist_allocate(TPL_N_arraylist * l, unsigned int size)
{
	assert(size > 0);
	if (size > l->capacity) {
		unsigned int new_capacity = l->capacity;
		while (new_capacity < size) {
			new_capacity *= 2;
		}
		l->body = realloc(l->body, sizeof(TPL_T) * new_capacity);
		assert(l->body);
		l->capacity = new_capacity;
	}
}


/**
 * Add item at the end of the list.
 */
void TPL_N_arraylist_add(TPL_N_arraylist * l, TPL_T item)
{
	TPL_N_arraylist_allocate(l, l->size + 1);
	l->body[l->size++] = item;
}

/**
 * Pop (remove and return) an item off the end of the list.
 */
TPL_T TPL_N_arraylist_pop(TPL_N_arraylist * l)
{
	assert(l->size > 0);
	return l->body[--l->size];
}

/**
 * Return item located at index.
 */
TPL_T TPL_N_arraylist_get(TPL_N_arraylist * l, unsigned int index)
{
	assert(index < l->size);
	return l->body[index];
}

/**
 * Replace item at index with given value.
 */
void TPL_N_arraylist_set(TPL_N_arraylist * l, unsigned int index, TPL_T value)
{
	assert(index < l->size);
	l->body[index] = value;
}

/**
 * Insert item at index, shifting the following items by one spot.
 */
void TPL_N_arraylist_insert(TPL_N_arraylist * l, unsigned int index, TPL_T value)
{
	// Reallocate, if needed
	TPL_N_arraylist_allocate(l, l->size + 1);
	// Move data to create a spot for the new value

	memshift(l->body + index, 1, l->size - index);
	l->body[index] = value;
	l->size++;
}

/**
 * Remove the item at index, shifting the following items back by one spot.
 */
TPL_T TPL_N_arraylist_remove(TPL_N_arraylist * l, unsigned int index)
{
	TPL_T value = l->body[index];
	//memmove(l->body + index, l->body + index + 1, (l->size - index) * sizeof(void*));
	memshift(l->body + index + 1, -1, l->size - index);
	l->size--;
	return value;
}

/**
 * Clear list of all items.
 */
void TPL_N_arraylist_clear(TPL_N_arraylist * l)
{
	l->size = 0;
}

/**
 * Return a slice of the list (of given length starting at index) as a new TPL_N_arraylist.
 */
TPL_N_arraylist * TPL_N_arraylist_slice(TPL_N_arraylist * l, unsigned int index, unsigned int length)
{
	assert(index + length <= l->size);
	TPL_N_arraylist * new_list = TPL_N_arraylist_create();
	TPL_N_arraylist_allocate(new_list, length);
	memmove(new_list->body, l->body + index, length * sizeof(TPL_T));
	new_list->size = length;
	return new_list;
}

/**
 * Return a slice of the list (from index to the end) as a new TPL_N_arraylist.
 */
TPL_N_arraylist * TPL_N_arraylist_slice_end(TPL_N_arraylist * l, unsigned int index)
{
	return TPL_N_arraylist_slice(l, index, l->size - index);
}

/**
 * Return a copy of the TPL_N_arraylist.
 */
TPL_N_arraylist * TPL_N_arraylist_copy(TPL_N_arraylist * l)
{
	return TPL_N_arraylist_slice_end(l, 0);
}

/**
 * Append a list onto another, in-place.
 */
void TPL_N_arraylist_join(TPL_N_arraylist * l, TPL_N_arraylist * source)
{
	TPL_N_arraylist_splice(l, source, l->size);
}

/**
 * Insert a list into another at the given index, in-place.
 */
void TPL_N_arraylist_splice(TPL_N_arraylist * l, TPL_N_arraylist * source, unsigned int index)
{
	// Reallocate, if needed
	TPL_N_arraylist_allocate(l, l->size + source->size);
	// Move data to the right
	memshift(l->body + index, source->size, l->size - index);
	//memmove(l->body + index + source->size, l->body + index, (l->size - index) * sizeof(void*));
	// Copy the data over
	memmove(l->body + index, source->body, source->size * sizeof(TPL_T));
	l->size += source->size;
}

void TPL_N_arraylist_destroy(TPL_N_arraylist * l)
{
	free(l->body);
	free(l);
}

