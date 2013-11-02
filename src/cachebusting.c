#include "cachebusting.h"

static cb_config* cachebusting_config;

int cb_init(void) { /* {{{ */
	cachebusting_config = (cb_config*)malloc(sizeof(cb_config));

	cachebusting_config->storage = MEMORY;
	cachebusting_config->cache_lifetime = 864000;
	cachebusting_config->revalidate_lifetime = 300;

	cachebusting_config->prefix = (char*)malloc(3);
	strncpy(cachebusting_config->prefix, "cb", 2);

	return 1;
}
/* }}} */

int cb_shutdown() { /* {{{ */
	free(cachebusting_config->prefix);
	free(cachebusting_config);

	return 1;
} 
/* }}} */

cb_config* cb_get_config() { /* {{{ */
	return cachebusting_config;
} 
/* }}} */


