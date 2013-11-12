#include <stdio.h>
#include "../dejagnu.h"
#include "../../src/item.h"

int main(void) {
	cb_item* item = NULL;
	item = cb_item_create("foo.c", "1234");
	if (item == NULL) {
		fail("fail to create item");
	} else {
		pass("Item created successfully");
	}

	if(strncmp("foo.c", item->filename, strlen("foo.c")) == 0) {
		pass("Filename correct");
	} else {
		fail("Filename incorrect");
	}
	
	if(strncmp("1234", item->hash, strlen("1234")) == 0) {
		pass("hash correct");
	} else {
		fail("hash incorrect");
	}

	/*cb_item_destroy(item);*/

	return 0;
}
