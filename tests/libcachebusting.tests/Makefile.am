AUTOMAKE_OPTIONS= dejagnu
EXTRA_DIST 		= libcachebusting.exp item_test.c list_test.c cachebusting_test.c utils_test.c

CLEANFILES 		= item_test list_test cachebusting_test utils_test

noinst_PROGRAMS = 
AM_CFLAGS = -g3 -O0
noinst_PROGRAMS += item_test
item_test_SOURCES = item_test.c ../dejagnu.h
item_test_LDADD = $(top_builddir)/src/libcachebusting.la

noinst_PROGRAMS += utils_test
utils_test_SOURCES = utils_test.c ../dejagnu.h
utils_test_LDADD = $(top_builddir)/src/libcachebusting.la

noinst_PROGRAMS += cachebusting_test
cachebusting_test_SOURCES = cachebusting_test.c ../dejagnu.h
cachebusting_test_LDADD = $(top_builddir)/src/libcachebusting.la

noinst_PROGRAMS += list_test
list_test_SOURCES = list_test.c ../dejagnu.h
list_test_LDADD = $(top_builddir)/src/libcachebusting.la
