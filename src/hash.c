#include <string.h>
#include <stdlib.h>
#include "hash.h"

unsigned long _hash(const char *key) {
	unsigned long hash = 5381;
	int c;

	while (c = *key++) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

/* {{{ Allocates memory for the hash map */
cb_hash* hash_create(int size) {
	cb_hash* hash = malloc(sizeof(struct _cb_hash));
	hash->size = size;
	hash->table = calloc(1, size * sizeof(cb_item));

	return hash;
}
/* }}} */

/* {{{ Free allocated memory */
void hash_destroy(cb_hash* hash) {
	if (!hash) 
		return;

	int i;
	for ( i = 0; i < hash->size; i++) {
		cb_item *item = hash->table[i];
		while (item) {
			cb_item *old_item = item;
			item = item->next;
			cb_item_destroy(old_item);
		}
	}

	free(hash->table);
	free(hash);
}
/* }}} */

/* {{{ Get item from hashtable */
cb_item* hash_get(cb_hash* hash, const char* key) {
	if (!hash) 
		return NULL;

	unsigned long id = _hash(key) % hash->size;
	cb_item *item = hash->table[id];
	while(item) {
		if (strncmp(key, item->filename, HT_MAX_KEYLEN) == 0) 
			return item;

		item = item->next;
	}

	return NULL;
}
/* }}} */

/* {{{ Add item to hashtable */
void hash_set(cb_hash* hash, cb_item *value) {
	if (!hash) 
		return;

	unsigned long id = _hash(value->filename) % hash->size;

	cb_item *item = calloc(1, sizeof(cb_item));
	item->hash = value->hash;
	item->filename = value->filename;

	item->next = hash->table[id];
	hash->table[id] = item;
}
/* }}} */

/* {{{ Remove entry from hashtable */
void hash_remove(cb_hash* hash, const char* key) {
	if (!hash) 
		return;

	unsigned long id = _hash(key) % hash->size;

	cb_item *p = NULL, *item = hash->table[id];
	while(item) {
		if (strncmp(key, item->filename, HT_MAX_KEYLEN) == 0) {
			if (p) 
				p->next = item->next;

			if (hash->table[id] == item) 
				hash->table[id] = NULL;
			
			break;
		}

		p = item;
		item = item->next;
	}
}
/* }}} */
