/**
 * Template for TPL_N_arraylist with element type: TPL_T
 */
typedef struct TPL_N_arraylist TPL_N_arraylist;
struct TPL_N_arraylist {
	unsigned int size; // Count of items currently in list
	unsigned int capacity; // Allocated memory size, in items
	TPL_T * body; // Pointer to allocated memory for items (of size capacity * sizeof(void*))
};
void TPL_N_arraylist_destroy(TPL_N_arraylist * l);
void TPL_N_arraylist_splice(TPL_N_arraylist * l, TPL_N_arraylist * source, unsigned int index);
void TPL_N_arraylist_join(TPL_N_arraylist * l, TPL_N_arraylist * source);
TPL_N_arraylist * TPL_N_arraylist_copy(TPL_N_arraylist * l);
TPL_N_arraylist * TPL_N_arraylist_slice_end(TPL_N_arraylist * l, unsigned int index);
TPL_N_arraylist * TPL_N_arraylist_slice(TPL_N_arraylist * l, unsigned int index, unsigned int length);
void TPL_N_arraylist_clear(TPL_N_arraylist * l);
TPL_T TPL_N_arraylist_remove(TPL_N_arraylist * l, unsigned int index);
void TPL_N_arraylist_insert(TPL_N_arraylist * l, unsigned int index, TPL_T value);
void TPL_N_arraylist_set(TPL_N_arraylist * l, unsigned int index, TPL_T value);
TPL_T TPL_N_arraylist_get(TPL_N_arraylist * l, unsigned int index);
TPL_T TPL_N_arraylist_pop(TPL_N_arraylist * l);
void TPL_N_arraylist_add(TPL_N_arraylist * l, TPL_T item);
void TPL_N_arraylist_allocate(TPL_N_arraylist * l, unsigned int size);
TPL_N_arraylist * TPL_N_arraylist_create();
#define TPL_N_arraylist_iterate(l, index, item)	\
	for (index = 0, item = l->body[0]; index < l->size; item = l->body[++index])
#define TPL_N_arraylist_size(l) (l->size)
