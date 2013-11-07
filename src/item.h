#ifndef __cb_item_h
#define __cb_item_h

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _cb_item {
	char* filename;
	char* hash;
	unsigned long timestamp;
	struct _cb_item *next;
} cb_item;

cb_item* cb_item_create(const char*, const char*);
void cb_item_destoy(cb_item*);

#ifdef __cplusplus
}
#endif

#endif
