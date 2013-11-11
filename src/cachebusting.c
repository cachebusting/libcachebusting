#include "cachebusting.h"
#include "hash.h"
#include <string.h>
#include <stdlib.h>

static cb_hash* hash;
static cb_config* cachebusting_config;

/* {{{ Create a cb_matches struct */
static cb_matches* cb_matches_create(void) {
	return calloc(1, sizeof(struct _cb_matches));
}
/* }}} */

/* {{{ Add a match to matches list */
static void cb_match_add(cb_matches* matches, int pos, char* hash) {
	cb_match *match = calloc(1, sizeof(struct _cb_match));
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


/* {{{ Rewrites html output with values from the hashmap.
 * This feature will be applied to:
 * - Image tags (<img src="...">)
 * - Script tags (<script src="...">)
 * - Link tags (<link href="...">)
 * */
extern char* cb_rewrite(char* content) {
	char const *tmpString, *from, *catString;
	char* findString;
	int length = strlen(content);
	int pos = 0;
	char delimiter;
	char* foo = "bar";

	cb_matches* matches = cb_matches_create();;
	findString = content;
	tmpString = content;
	catString = content;
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
		cb_item* item = hash_get(hash, str);
		if (item != NULL) {
			cb_match_add(matches, findString - tmpString, item->hash);
			tmpString = findString;
		}
		free(str);
	}

	if (matches->count <= 0) 
		return content;

	int end = 0, newlen;
	newlen = length + (matches->count*9)+1;
	char *new_content = calloc(1, newlen);
	cb_match* match = matches->first;
	while(1) {
		strncat(new_content, catString, match->pos);
		strncat(new_content, ";cb", 3);
		strncat(new_content, match->hash, strlen(match->hash) < 6 ? strlen(match->hash) : 6);
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
extern int cb_shutdown() {
	hash_destroy(hash);
	free(cachebusting_config->prefix);
	free(cachebusting_config);

	return 1;
} 
/* }}} */

