#ifndef __cb_list_h
#define __cb_list_h

#include "item.h"

typedef struct _cb_list {
	cb_item* next;
} cb_list;

int cb_list_init(void);

#endif
