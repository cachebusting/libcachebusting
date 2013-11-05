#ifndef __cachebusting_h
#define __cachebusting_h

#ifdef __cplusplus
extern "C"
#endif

#define MEMORY 0
#define REDIS 1
#define MONGO 2

typedef struct _cb_config {
	char storage;
	int cache_lifetime;
	int revalidate_lifetime;
	char* prefix;
} cb_config;

int cb_init(void);
int cb_shutdown(void);
cb_config* cb_get_config(void);

#ifdef __cplusplus
}
#endif

#endif
