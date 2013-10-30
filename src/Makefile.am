ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libcachebusting.la
libcachebusting_la_SOURCES = cachebusting.c item.c list.c
pkginclude_HEADERS = cachebusting.h item.h list.h
libcachebusting_ladir = $(includedir)/cachebusting
libcachebusting_la_LDFLAGS = -module -avoid-version

cachebusting_includedir = $(includedir)/cachebusting
