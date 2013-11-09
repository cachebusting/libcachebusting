#include "../dejagnu.h"
#include "../../src/cachebusting.h"
#include <stdlib.h>

int main (void) {
	cb_init();
	cb_config* config;
	config = cb_get_config();

	if (config->cache_lifetime == 864000) {
		pass("Default cache lifetime");
	} else {
		fail("Wrong default cache lifetime");
	}

	if (config->revalidate_lifetime == 300) {
		pass("Default revalidate lifetime");
	} else {
		fail("Wrong default revalidate lifetime");
	}

	if (strncmp("cb", config->prefix, 2) == 0) {
		pass("Default prefix value");
	} else {
		fail("Wrong default prefix");
	}

	char buffer [5];
	int i;
	for(i = 0; i < 100; i++) {
		sprintf(buffer, "%d", i);
		cb_item* item = cb_item_create(buffer, "test");
		cb_add(item);
	}

	int fails = 0;
	for(i = 0; i < 100; i++) {
		sprintf(buffer, "%d", i);
		cb_item* item = cb_get(buffer);
		if(strncmp("test", item->hash, 4) != 0) {
			fails++;
		}
	}
	if (fails) {
		fail("Retrieved different items");
	} else {
		pass("Retrieved same items");
	}

	cb_item* item = cb_get("test");
	if (item == NULL) {
		pass("Expected missed value");
	} else {
		fail("Unexpected missed value");
	}

	cb_shutdown();

	if (strncmp("cb", config->prefix, 2) == 0) {
		fail("Fail in cb_shutdown");
	} else {
		pass("Correctly cleaned up");
	}

	return EXIT_SUCCESS;
}
