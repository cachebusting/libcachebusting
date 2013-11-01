AUTOMAKE_OPTIONS= dejagnu
EXTRA_DIST 		= libcachebusting.exp item_test.c

CLEANFILES 		= item_test

noinst_PROGRAMS = 

noinst_PROGRAMS += item_test
item_test_SOURCES = item_test.c
item_test_LDADD = $(top_builddir)/src/libcachebusting.la

noinst_PROGRAMS += utils_test
utils_test_SOURCES = utils_test.c
utils_test_LDADD = $(top_builddir)/src/libcachebusting.la

noinst_PROGRAMS += cachebusting_test
cachebusting_test_SOURCES = cachebusting_test.c
cachebusting_test_LDADD = $(top_builddir)/src/libcachebusting.la
