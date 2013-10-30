#ifndef __cb_item_h
#define __cb_item_h

typedef struct _cb_item {
	char* filename;
	char* hash;
} cb_item;

cb_item* cb_item_create(const char*, const char*);

#endif
