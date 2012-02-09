#pragma once
typedef struct TPL_N_hashtable TPL_N_hashtable;
void TPL_N_hashtable_destroy(TPL_N_hashtable *t);
typedef struct TPL_N_hashtable_entry TPL_N_hashtable_entry;
TPL_N_hashtable_entry *TPL_N_hashtable_body_allocate(unsigned int capacity);
TPL_N_hashtable *TPL_N_hashtable_create();
void TPL_N_hashtable_remove(TPL_N_hashtable *t,char *key);
void TPL_N_hashtable_resize(TPL_N_hashtable *t,unsigned int capacity);
void TPL_N_hashtable_set(TPL_N_hashtable *t,char *key,TPL_T value);
int TPL_N_hashtable_get(TPL_N_hashtable *t,char *key, TPL_T* ptr);
unsigned int TPL_N_hashtable_find_slot(TPL_N_hashtable *t,char *key);
unsigned long TPL_N_hashtable_hash(char *str);
struct TPL_N_hashtable {
	unsigned int size;
	unsigned int capacity;
	TPL_N_hashtable_entry* body;
};
struct TPL_N_hashtable_entry {
	char* key;
	TPL_T  value;
};
