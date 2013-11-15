#include "cachebusting.h"
#include "hash.h"
#include <string.h>
#include <stdlib.h>

/* {{{ Create a cb_matches struct */
static cb_matches* cb_matches_create(void) {
	return calloc(1, sizeof(cb_matches));
}
/* }}} */

/* {{{ Add a match to matches list */
static void cb_match_add(cb_matches* matches, int pos, char* hash) {
	cb_match *match = calloc(1, sizeof(cb_match));
	match->hash = hash;
	match->pos = pos;

	if(matches->last == NULL) {
		matches->first = match;
		matches->last = match;
	} else {
		matches->last->next = match;
		match->prev = matches->last;
		matches->last = match;
	}

	matches->count++;
}
/* }}} */

/* {{{ Free the matches struct */
static void cb_matches_destroy(cb_matches *matches) {
	cb_match *node = NULL, *cur = NULL;
	for(cur = node = matches->first; node != NULL; cur = node = node->next) {
		if(cur->prev) free(cur->prev);
	}

	free(matches->last);
	free(matches);
}
/* }}} */

/* {{{ Initialize cache busting */
extern cb_config* cb_init(void) { 
	cb_config* cachebusting_config = (cb_config*)malloc(sizeof(cb_config));
	cachebusting_config->hashtable = hash_create(200);

	cachebusting_config->cache_lifetime = 864000;
	cachebusting_config->revalidate_lifetime = 300;

	cachebusting_config->prefix = (char*)malloc(3);
	strncpy(cachebusting_config->prefix, "cb", 3);

	return cachebusting_config;
}
/* }}} */

/* {{{ Get item from hashtable */
extern cb_item* cb_get(cb_hash* hash, const char* key) {
	return hash_get(hash, key);
}
/* }}} */

/* {{{ Add item to hashtable */
extern int cb_add(cb_hash* hash, cb_item* item) {
	hash_set(hash, item);

	return 1;
}
/* }}} */


/* {{{ Rewrites html output with values from the hashmap.
 * This feature will be applied to:
 * - Image tags (<img src="...">)
 * - Script tags (<script src="...">)
 * - Link tags (<link href="...">)
 * */
extern char* cb_rewrite(cb_config* cachebusting_config, char* content) {
	char const *tmpString, *from, *catString;
	char* findString;
	int length = strlen(content);
	int pos = 0;
	char delimiter;

	cb_matches* matches = cb_matches_create();;
	findString = tmpString = catString = content;
	
	while(1) {
		findString = strstr(findString, "img");
		if (findString == NULL) break;

		while(1) {
			if (*findString == '\'') {
				delimiter = '\'';
				findString++;
				break;
			}
			if (*findString == '\"') {
				delimiter = '\"';
				findString++;
				break;
			}
			findString++;
		}
		from = findString;

		int count = 0;
		while(*findString != delimiter) {
			findString++;
			count++;
			pos++;
		}

		char* str;
		str = calloc(1, count+1);
		strncpy(str, from, count);
		cb_item* item = hash_get(cachebusting_config->hashtable, str);
		if (item != NULL) {
			cb_match_add(matches, findString - tmpString, item->hash);
			tmpString = findString;
		}
		free(str);
	}

	if (matches->count <= 0) 
		return content;

	int end = 0, newlen;
	newlen = length + (matches->count * (HASH_LEN + strlen(cachebusting_config->prefix)+1))+1;
	char *new_content = calloc(1, newlen);
	cb_match* match = matches->first;
	while(1) {
		strncat(new_content, catString, match->pos);
		strncat(new_content, ";", 1);
		strncat(new_content, cachebusting_config->prefix, strlen(cachebusting_config->prefix));
		strncat(new_content, match->hash, strlen(match->hash) < HASH_LEN ? strlen(match->hash) : HASH_LEN);
		catString += match->pos;
		end += match->pos;
		if (!match->next) break;
		match = match->next;
	}
	int rest = length - end;
	strncat(new_content, catString, rest);
	cb_matches_destroy(matches);

	return new_content;
}
/* }}} */

/* {{{ Free allocated memory */
extern int cb_shutdown(cb_config* cachebusting_config) {
	hash_destroy(cachebusting_config->hashtable);
	free(cachebusting_config->prefix);
	free(cachebusting_config);

	return 1;
} 
/* }}} */

