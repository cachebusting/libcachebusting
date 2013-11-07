ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libcachebusting.la
libcachebusting_la_SOURCES = cachebusting.c hash.c item.c utils.c
pkginclude_HEADERS = cachebusting.h hash.h item.h utils.h
libcachebusting_ladir = $(includedir)/cachebusting
libcachebusting_la_LDFLAGS = -module -avoid-version

cachebusting_includedir = $(includedir)/cachebusting
