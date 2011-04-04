/* This file was automatically generated.  Do not edit! */
typedef struct alht_al alht_al;
void *alht_al_pop(alht_al *l);
void alht_al_add(alht_al *l,void *item);
void alht_al_allocate(alht_al *l,unsigned int capacity);
alht_al *alht_al_create();
struct alht_al {
	unsigned int size;
	unsigned int capacity;
	void** body;
};
#define alht_al_iterate(l, index, item) \
	for (index = 0; index < l->size; item = index[i++])
#define INTERFACE 0
