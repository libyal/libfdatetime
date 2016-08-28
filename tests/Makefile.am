AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBFDATETIME_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_api_types.sh 

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fdatetime_test_error \
	fdatetime_test_fat_date_time \
	fdatetime_test_filetime \
	fdatetime_test_floatingtime \
	fdatetime_test_get_version \
	fdatetime_test_hfs_time \
	fdatetime_test_nsf_timedate_copy_from \
	fdatetime_test_nsf_timedate_to_string \
	fdatetime_test_posix_time \
	fdatetime_test_systemtime_copy_from \
	fdatetime_test_systemtime_to_string

fdatetime_test_error_SOURCES = \
	fdatetime_test_error.c \
	fdatetime_test_libcstring.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_unused.h

fdatetime_test_error_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCSTRING_LIBADD@

fdatetime_test_fat_date_time_SOURCES = \
	fdatetime_test_fat_date_time.c \
	fdatetime_test_libcstring.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_memory.c fdatetime_test_memory.h \
	fdatetime_test_unused.h

fdatetime_test_fat_date_time_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

fdatetime_test_filetime_SOURCES = \
	fdatetime_test_filetime.c \
	fdatetime_test_libcstring.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_memory.c fdatetime_test_memory.h \
	fdatetime_test_unused.h

fdatetime_test_filetime_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

fdatetime_test_floatingtime_SOURCES = \
	fdatetime_test_floatingtime.c \
	fdatetime_test_libcstring.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_memory.c fdatetime_test_memory.h \
	fdatetime_test_unused.h

fdatetime_test_floatingtime_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

fdatetime_test_get_version_SOURCES = \
	fdatetime_test_get_version.c \
	fdatetime_test_libcstring.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_unused.h

fdatetime_test_get_version_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCSTRING_LIBADD@

fdatetime_test_hfs_time_SOURCES = \
	fdatetime_test_hfs_time.c \
	fdatetime_test_libcstring.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_memory.c fdatetime_test_memory.h \
	fdatetime_test_unused.h

fdatetime_test_hfs_time_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

fdatetime_test_nsf_timedate_copy_from_SOURCES = \
	fdatetime_test_libcerror.h \
	fdatetime_test_libcstring.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_nsf_timedate_copy_from.c

fdatetime_test_nsf_timedate_copy_from_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

fdatetime_test_nsf_timedate_to_string_SOURCES = \
	fdatetime_test_libcerror.h \
	fdatetime_test_libcstring.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_nsf_timedate_to_string.c

fdatetime_test_nsf_timedate_to_string_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

fdatetime_test_posix_time_SOURCES = \
	fdatetime_test_libcstring.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_memory.c fdatetime_test_memory.h \
	fdatetime_test_posix_time.c \
	fdatetime_test_unused.h

fdatetime_test_posix_time_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

fdatetime_test_systemtime_copy_from_SOURCES = \
	fdatetime_test_libcerror.h \
	fdatetime_test_libcstring.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_systemtime_copy_from.c

fdatetime_test_systemtime_copy_from_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

fdatetime_test_systemtime_to_string_SOURCES = \
	fdatetime_test_libcerror.h \
	fdatetime_test_libcstring.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_systemtime_to_string.c

fdatetime_test_systemtime_to_string_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

