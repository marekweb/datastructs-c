/* This file was automatically generated.  Do not edit! */
typedef struct hashtable hashtable;
void hashtable_destroy(hashtable *t);
void hashtable_remove(hashtable *t,char *key);
void *hashtable_get(hashtable *t,char *key);
void hashtable_set(hashtable *t,char *key,void *value);
hashtable *hashtable_create();
typedef struct hashtable_entry hashtable_entry;
struct hashtable {
	unsigned int size;
	unsigned int capacity;
	hashtable_entry* body;
};
typedef struct arraylist arraylist;
void arraylist_destroy(arraylist *l);
void arraylist_clear(arraylist *l);
#define arraylist_iterate(l, index, item) \
	for (index = 0, item = l->body[0]; index < l->size; item = l->body[++index])
arraylist *arraylist_copy(arraylist *l);
arraylist *arraylist_slice(arraylist *l,unsigned int index,unsigned int length);
void *arraylist_remove(arraylist *l,unsigned int index);
void arraylist_insert(arraylist *l,unsigned int index,void *value);
void *arraylist_pop(arraylist *l);
void *arraylist_get(arraylist *l,unsigned int index);
void arraylist_add(arraylist *l,void *item);
arraylist *arraylist_create();
struct arraylist {
	unsigned int size; // Count of items currently in list
	unsigned int capacity; // Allocated memory size, in items
	void** body; // Pointer to allocated memory for items (of size capacity * sizeof(void*))
};
int main();
struct hashtable_entry {
	char* key;
	void* value;
};
