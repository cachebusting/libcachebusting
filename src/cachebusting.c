#include "cachebusting.h"
#include "hash.h"
#include <string.h>
#include <stdlib.h>

static cb_hash* hash;
static cb_config* cachebusting_config;

/* {{{ Initialize cache busting */
extern int cb_init(void) { 
	cachebusting_config = (cb_config*)malloc(sizeof(cb_config));
	hash = hash_create(200);

	cachebusting_config->cache_lifetime = 864000;
	cachebusting_config->revalidate_lifetime = 300;

	cachebusting_config->prefix = (char*)malloc(3);
	strncpy(cachebusting_config->prefix, "cb", 2);

	return 1;
}
/* }}} */

/* {{{ Retrieves cachebusting config */
extern cb_config* cb_get_config() {
	return cachebusting_config;
}
/* }}} */

/* {{{ Get item from hashtable */
extern cb_item* cb_get(const char* key) {
	return hash_get(hash, key);
}
/* }}} */

/* {{{ Add item to hashtable */
extern int cb_add(cb_item* item) {
	hash_set(hash, item);

	return 1;
}
/* }}} */

/* {{{ Free allocated memory */
extern int cb_shutdown() {
	free(cachebusting_config->prefix);
	free(cachebusting_config);
	hash_destroy(hash);

	return 1;
} 
/* }}} */

