/* This file was automatically generated.  Do not edit! */
typedef struct alht_ht_entry alht_ht_entry;
alht_ht_entry *alht_ht_body_allocate(unsigned int capacity);
typedef struct alht_ht alht_ht;
alht_ht *alht_ht_create();
void *alht_ht_remove(alht_ht *t,char *key);
void alht_ht_resize(alht_ht *t,unsigned int capacity);
void *alht_ht_set(alht_ht *t,char *key,void *value);
void *alht_ht_get(alht_ht *t,char *key);
unsigned int alht_ht_find_slot(alht_ht *t,char *key);
unsigned long alht_ht_hash(char *str);
struct alht_ht {
	unsigned int size;
	unsigned int capacity;
	alht_ht_entry* body;
};
struct alht_ht_entry {
	char* key;
	void* value; 
};
#define INTERFACE 0
