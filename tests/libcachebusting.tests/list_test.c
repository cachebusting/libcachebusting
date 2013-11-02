#include "../dejagnu.h"
#include "../../src/list.h"

void main(void) {
	cb_list* list = NULL;
	list = cb_list_create(sizeof(cb_item), 1000);
	if (list != NULL) {
		pass("List created successfulls");
	} else {
		fail("List not created");
	}
	cb_item* item = NULL;
	item = cb_item_create("test1", "12345");
	cb_list_push(list, item);

	cb_item* item2 = NULL;
	item2 = cb_list_pop(list);

	if (strcmp(item2->filename, item->filename) == 0) {
		pass("Same item from push and pop");
	} else {
		fail("Different item from push and pop");
	}

	cb_list_clear(list);

	int i, o = 0;
	char buffer [5];
	for(i = 0; i < 1000; i++) {
		sprintf(buffer, "%d", i);
		cb_item* item = cb_item_create(buffer, "abcde");
		cb_list_push(list, item);
	}

	int fails = 0;
	for(o = 0; o < 1000; o++) {
		sprintf(buffer, "%d", o);
		cb_item* item = list->items[o];
		if (strcmp(item->filename, buffer) != 0 || strncmp("abcde", item->hash, 5) != 0) {
			fails++;
		} 
	}

	if (fails) {
		fail("One of thousand elements fails");
	} else {
		pass("Thousand elements are fine");
	}

}
