#include "../dejagnu.h"
#include "../../src/cachebusting.h"

void main (void) {
	cb_init();
	cb_config* config;
	config = cb_get_config();

	if (config->storage == MEMORY) {
		pass("Default storage value");
	} else {
		fail("Wrong default storage value");
	}

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

	cb_shutdown();

	if (strncmp("cb", config->prefix, 2) != 0) {
		fail("Fail in cb_shutdown");
	} else {
		pass("Correctly cleaned up");
	}
}
