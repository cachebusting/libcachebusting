#ifndef __cachebusting_h
#define __cachebusting_h

typedef struct _cb_item {
	char* file;
	char* hash;
} cb_item;

int cb_init(void);

#endif
