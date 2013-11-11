#include <stdio.h>
#include <stdlib.h>
#include "../dejagnu.h"
#include "../../src/hash.h"
#include "../../src/item.h"

int main(void) {
	cb_hash *hashtable = NULL;
	hashtable =	hash_create(200);
	if (hashtable != NULL) {
		pass("Hashtable correct created");
	} else {
		fail("Hashtable failed to allocate");
	}
	cb_item* foo = cb_item_create("foo", "bar");
	hash_set(hashtable, foo);
	hash_set(hashtable, cb_item_create("bar", "foo"));
	cb_item* item = hash_get(hashtable, "foo");
	cb_item* item1 = hash_get(hashtable, "bar");

	if (strncmp(item->filename, "foo", 3) == 0 && strncmp(item->hash, "bar", 3) == 0) {
		pass("Put and Get retrieved the same element");
	} else {
		fail("Put and Get retrieved different elements");
	}

	if (strncmp(item1->filename, "bar", 3) == 0 && strncmp(item1->hash, "foo", 3) == 0) {
		pass("Put and Get retrieved the same element");
	} else {
		fail("Put and Get retrieved different elements");
	}
	hash_destroy(hashtable);
	cb_item_destroy(foo);

	return EXIT_SUCCESS;
}
