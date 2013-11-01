#include <time.h>

unsigned long cb_timestamp(void) {
	time_t timer;
	time(&timer);

	return (unsigned long)timer;
}
