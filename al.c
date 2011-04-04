#include <stdlib.h>
#include <assert.h>
#include "al.h"

#if INTERFACE
#define alht_al_iterate(l, index, item) \
	for (index = 0; index < l->size; item = index[i++])
	
struct alht_al {
	unsigned int size;
	unsigned int capacity;
	void** body;
};
#endif

#define ALHT_AL_CAPACITY 4

alht_al* alht_al_create() {
	alht_al* new_list = malloc(sizeof(alht_al));
	new_list->size = 0;
	alht_al_allocate(new_list, ALHT_AL_CAPACITY);
	return new_list;
}

void alht_al_allocate(alht_al* l, unsigned int capacity) {
	assert(capacity >= l->size);
	l->body = realloc(l->body, sizeof(void*) * capacity);
	l->capacity = capacity;
}

void alht_al_add(alht_al* l, void* item) {
	if (l->size == l->capacity) {
		alht_al_allocate(l, l->capacity * 2);
	}
	(l->body)[l->size++] = item;
}

void* alht_al_pop(alht_al* l) {
	assert(l->size > 0);
	return (l->body)[--l->size];
}

