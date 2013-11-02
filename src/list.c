#include "list.h"
#include <stdlib.h>
#include <string.h>

static inline int cb_list_resize(cb_list* list, size_t newsize) {
	list->max = newsize;
	cb_item* item = realloc(list->items, list->max * sizeof(cb_item));

	list->items = item;

	return 0;
}

cb_list* cb_list_create(size_t element_size, size_t initial_max) {
	cb_list* list = malloc(sizeof(cb_list));
	list->max = initial_max;
	list->items = calloc(initial_max, sizeof(cb_item));
	list->element_size = element_size;
	list->expand_rate = DEFAULT_EXPAND_RATE;

	return list;
}

void cb_list_destroy(cb_list* list) {
	if (list) {
		if (list->items) free(list->items);
		free(list);
	}
}

int cb_list_expand(cb_list* list) {
	size_t old_max = list->max;
	cb_list_resize(list, list->max + list->expand_rate);
	memset(list->items + old_max, 0, list->expand_rate + 1);

	return 0;
}

int cb_list_push(cb_list* list, cb_item* item) {
	list->items[list->end] = item;
	list->end++;

	if (list->end >= list->max) {
		return cb_list_expand(list);
	} else {
		return 0;
	}
}

cb_item* cb_list_pop(cb_list* list) {
	cb_item* item = cb_list_remove(list, list->end - 1);
	list->end--;

	if(list->end > (int)list->expand_rate && list->end % list->expand_rate) {
		cb_list_contract(list);
	}

	return item;
}


int cb_list_contract(cb_list* list) {
	int new_size = list->end < (int)list->expand_rate ? (int)list->expand_rate : list->end;

	return cb_list_resize(list, new_size);
}

void cb_list_clear(cb_list* list) {
	int i = 0;
	if (list->element_size > 0) {
		for (i = 0; i < list->max; i++) {
			if (list->items[i] != NULL) {
				cb_item_destroy(list->items[i]);
			}
		}
	}
}
