#include <string.h>
#include "item.h"

cb_item* cb_item_create(const char* filename, const char* hash) {
	cb_item* item = (cb_item*)malloc(sizeof(cb_item));
	size_t filename_size = strlen(filename);
	size_t hash_size = strlen(hash);
	item->filename = (char*)malloc(filename_size);
	strncpy(item->filename, filename, filename_size);
	item->hash = (char*)malloc(hash_size);
	strncpy(item->hash, hash, hash_size);

	return item;
}
