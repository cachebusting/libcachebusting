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

extern int cb_init(void);
extern int cb_shutdown(void);
extern cb_config* cb_get_config(void);
extern int cb_add(cb_item*);
extern cb_item* cb_get(const char*);

#ifdef __cplusplus
}
#endif

#endif
