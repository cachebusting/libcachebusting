#ifndef __cb_hash_h
#define __cb_hash_h

#ifdef __cplusplus
extern "C" {
#endif

#include "item.h"

#define HT_MAX_KEYLEN 255

typedef struct _cb_hash {
	cb_item **table;
	int size;
} cb_hash;

cb_hash* hash_create(int size);						/* Allocate hashtable size  */
void hash_destroy(cb_hash *ht);						/* Free hashtable memory */
cb_item* hash_get(cb_hash *ht, char* key);			/* Retrieve entry */
void hash_set(cb_hash* ht, cb_item* value);			/* Store entry */
void hash_remove(cb_hash* ht, char* key);			/* Remove entry*/

#ifdef __cplusplus
}
#endif

#endif
