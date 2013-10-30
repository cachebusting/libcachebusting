#include <stdio.h>
#include <dejagnu.h>
#include "../../src/item.h"

int main(void) {
	cb_item* item = NULL;
/*	item = cb_item_create("foo.c", "1234");*/
	if (item == NULL) {
		fail("fail to create item");
	} else {
		pass("Item created successfully");
	}
	pass("foo");
	totals();
	return 0;
}
