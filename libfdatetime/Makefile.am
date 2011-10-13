AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/liberror \
	@MEMWATCH_CPPFLAGS@

lib_LTLIBRARIES = libfdatetime.la

libfdatetime_la_SOURCES = \
	libfdatetime_date_time_values.c libfdatetime_date_time_values.h \
	libfdatetime_definitions.h \
	libfdatetime_extern.h \
	libfdatetime_error.c libfdatetime_error.h \
	libfdatetime_fat_date_time.c libfdatetime_fat_date_time.h \
	libfdatetime_filetime.c libfdatetime_filetime.h \
	libfdatetime_nsf_timedate.c libfdatetime_nsf_timedate.h \
	libfdatetime_posix_time.c libfdatetime_posix_time.h \
	libfdatetime_support.c libfdatetime_support.h \
	libfdatetime_types.h

libfdatetime_la_LIBADD = \
	../liberror/liberror.la

libfdatetime_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libfdatetime_definitions.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libfdatetime_definitions.h
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libfdatetime ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libfdatetime_la_SOURCES) 

