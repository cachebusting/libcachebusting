#include <unistd.h>
#include "../dejagnu.h"
#include "../../src/utils.h"

void main (void) {
	unsigned long timer = cb_timestamp();
	if (timer) {
		pass("Timestamp returns value");
	} else {
		fail("Timestamp returns no value");
	}
	sleep(1);
	unsigned long new_timer = cb_timestamp();

	if (new_timer > timer) {
		pass("Timer greater after sleep");
	} else {
		fail("Timer isn't greater after sleep");
	}
}
