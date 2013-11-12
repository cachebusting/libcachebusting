#include "../dejagnu.h"
#include "../../src/cachebusting.h"
#include <stdlib.h>

int main (void) {
	cb_init();
	cb_config* config;
	config = cb_get_config();

	if (config->cache_lifetime == 864000) {
		pass("Default cache lifetime");
	} else {
		fail("Wrong default cache lifetime");
	}

	if (config->revalidate_lifetime == 300) {
		pass("Default revalidate lifetime");
	} else {
		fail("Wrong default revalidate lifetime");
	}

	if (strncmp("cb", config->prefix, 2) == 0) {
		pass("Default prefix value");
	} else {
		fail("Wrong default prefix");
	}

	char buffer [5];
	int i;
	for(i = 0; i < 100; i++) {
		sprintf(buffer, "%d", i);
		cb_item* item = cb_item_create(buffer, "test");
		cb_add(item);
	}

	int fails = 0;
	for(i = 0; i < 100; i++) {
		sprintf(buffer, "%d", i);
		cb_item* item = cb_get(buffer);
		if(strncmp("test", item->hash, 4) != 0) {
			fails++;
		}
	}
	if (fails) {
		fail("Retrieved different items");
	} else {
		pass("Retrieved same items");
	}

	cb_item* item = cb_get("test");
	if (item == NULL) {
		pass("Expected missed value");
	} else {
		fail("Unexpected missed value");
	}

	cb_shutdown();

	cb_init();
	cb_add(cb_item_create("foo", "bar"));
	const char* content = "kasdldadsm <img src='foo'/>";
	char* result = cb_rewrite(content);
	cb_shutdown();
	
	if(strlen(result) > strlen(content)) {
		if (strncmp("kasdldadsm <img src='foo;cbbar'/>", result, strlen("kasdldadsm <img src='foo;cbbar'/>")) == 0) {
			pass("Very simple rewrite passed");
		} else {
			fail("Simple rewrite failed");
		}
	} else {
		fail("Simple rewrite failed");
	}
	free(result);

	cb_init();
	cb_item* item1 = cb_item_create("/i/am/a/test.png", "123456");
	cb_item* item2 = cb_item_create("/i/am/a/test2.png", "654321");
	cb_add(item1);
	cb_add(item2);
	const char* bigcontent = "<!doctype html> \
		<html> \
		<head> \
		    <title>Example Domain</title> \
			\
			    <meta charset=\"utf-8\" /> \
				    <meta http-equiv=\"Content-type\" content=\"text/html; charset=utf-8\" /> \
					    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /> \
						    <style type=\"text/css\"> \
							    body { \
								        background-color: #f0f0f2; \
								        margin: 0; \
								        padding: 0; \
								        font-family: \"Open Sans\", \"Helvetica Neue\", Helvetica, Arial, sans-serif; \
								        \
								    } \
	    div { \
		        width: 600px; \
		        margin: 5em auto; \
		        padding: 50px; \
		        background-color: #fff; \
		        border-radius: 1em; \
		    } \
		    a:link, a:visited { \
			          color: #38488f; \
			          text-decoration: none; \
			      } \
			      @media (max-width: 700px) { \
				          body { \
						              background-color: #fff; \
						          } \
				          div { \
						              width: auto; \
						              margin: 0 auto; \
						              border-radius: 0; \
						              padding: 1em; \
						          } \
				      } \
				      </style>     \
						  </head> \
						   \
						  <body> \
						  <div> \
						      <h1>Example Domain</h1> \
							      <p><img src=\"/i/am/a/test.png\"/>This domain is established to be used for illustrative examples in documents. You may use this \
								      domain in examples without prior coordination or asking for permission.<img src=\"/i/am/a/test2.png\"/>/p> \
									      <p><a href=\"http://www.iana.org/domains/example\">More information...</a></p> \
										  </div> \
										  </body> \
										  </html>";
	const char* expectedresult = "<!doctype html> \
		<html> \
		<head> \
		    <title>Example Domain</title> \
			\
			    <meta charset=\"utf-8\" /> \
				    <meta http-equiv=\"Content-type\" content=\"text/html; charset=utf-8\" /> \
					    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /> \
						    <style type=\"text/css\"> \
							    body { \
								        background-color: #f0f0f2; \
								        margin: 0; \
								        padding: 0; \
								        font-family: \"Open Sans\", \"Helvetica Neue\", Helvetica, Arial, sans-serif; \
								        \
								    } \
	    div { \
		        width: 600px; \
		        margin: 5em auto; \
		        padding: 50px; \
		        background-color: #fff; \
		        border-radius: 1em; \
		    } \
		    a:link, a:visited { \
			          color: #38488f; \
			          text-decoration: none; \
			      } \
			      @media (max-width: 700px) { \
				          body { \
						              background-color: #fff; \
						          } \
				          div { \
						              width: auto; \
						              margin: 0 auto; \
						              border-radius: 0; \
						              padding: 1em; \
						          } \
				      } \
				      </style>     \
						  </head> \
						   \
						  <body> \
						  <div> \
						      <h1>Example Domain</h1> \
							      <p><img src=\"/i/am/a/test.png;cb123456\"/>This domain is established to be used for illustrative examples in documents. You may use this \
								      domain in examples without prior coordination or asking for permission.<img src=\"/i/am/a/test2.png;cb654321\"/>/p> \
									      <p><a href=\"http://www.iana.org/domains/example\">More information...</a></p> \
										  </div> \
										  </body> \
										  </html>";
	char* bigresult = cb_rewrite(bigcontent);
	if(strlen(bigresult) > strlen(bigcontent)) {
		if (strncmp(bigresult, expectedresult, strlen(expectedresult)) == 0) {
			pass("Complex rewrite passed");
		} else {
			fail("Complex rewrite failed");
		}
	} else {
		fail("Simple rewrite failed");
	}
	free(bigresult);
	cb_shutdown();

	return EXIT_SUCCESS;
}
