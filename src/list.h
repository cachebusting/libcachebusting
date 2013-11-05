#ifndef __cb_list_h
#define __cb_list_h

#ifdef __cplusplus
extern "C" {
#endif

#include "item.h"
#include <stdlib.h>

#define DEFAULT_EXPAND_RATE 300

typedef struct _cb_list {
	int end;
	int max;
	size_t element_size;
	size_t expand_rate;
	cb_item** items;
} cb_list;

cb_list* cb_list_create(size_t element_size, size_t initial_max);
void cb_list_destroy(cb_list* list);
int cb_list_expand(cb_list* list);
int cb_list_push(cb_list* list, cb_item* item);
void cb_list_clear(cb_list* list);
cb_item* cb_list_pop(cb_list* list);
int cb_list_contract(cb_list*);

static inline cb_item* cb_list_remove(cb_list* list, int i) {
	cb_item* item = list->items[i];
	list->items[i] = NULL;

	return item;
}

#ifdef __cplusplus
}
#endif

#endif
