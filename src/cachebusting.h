#ifndef __cachebusting_h
#define __cachebusting_h

#ifdef __cplusplus
extern "C" {
#endif

#include "item.h"

typedef struct _cb_config {
	int cache_lifetime;
	int revalidate_lifetime;
	char* prefix;
} cb_config;

typedef struct _cb_match {
	unsigned int pos;
	char* hash;
	struct _cb_match *next;
	struct _cb_match *prev;
} cb_match;

typedef struct _cb_matches {
	int count;
	struct _cb_match *first;
	struct _cb_match *last;
} cb_matches;

static cb_matches* cb_matches_create(void);
static void cb_match_add(cb_matches*, int, char*);
static void cb_matches_destroy(cb_matches*);

extern int cb_init(void);
extern int cb_shutdown(void);
extern cb_config* cb_get_config(void);
extern int cb_add(cb_item*);
extern cb_item* cb_get(const char*);
extern char* cb_rewrite(char*);

#ifdef __cplusplus
}
#endif

#endif
