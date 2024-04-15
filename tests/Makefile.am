AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBFDATETIME_DLL_IMPORT@

TESTS = \
	test_library.sh

check_SCRIPTS = \
	test_library.sh \
	test_manpage.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fdatetime_test_date_time_values \
	fdatetime_test_error \
	fdatetime_test_fat_date_time \
	fdatetime_test_filetime \
	fdatetime_test_floatingtime \
	fdatetime_test_hfs_time \
	fdatetime_test_nsf_timedate \
	fdatetime_test_posix_time \
	fdatetime_test_support \
	fdatetime_test_systemtime

fdatetime_test_date_time_values_SOURCES = \
	fdatetime_test_date_time_values.c \
	fdatetime_test_libcerror.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_memory.c fdatetime_test_memory.h \
	fdatetime_test_unused.h

fdatetime_test_date_time_values_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@

fdatetime_test_error_SOURCES = \
	fdatetime_test_error.c \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_unused.h

fdatetime_test_error_LDADD = \
	../libfdatetime/libfdatetime.la

fdatetime_test_fat_date_time_SOURCES = \
	fdatetime_test_fat_date_time.c \
	fdatetime_test_libcerror.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_memory.c fdatetime_test_memory.h \
	fdatetime_test_unused.h

fdatetime_test_fat_date_time_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@

fdatetime_test_filetime_SOURCES = \
	fdatetime_test_filetime.c \
	fdatetime_test_libcerror.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_memory.c fdatetime_test_memory.h \
	fdatetime_test_unused.h

fdatetime_test_filetime_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@

fdatetime_test_floatingtime_SOURCES = \
	fdatetime_test_floatingtime.c \
	fdatetime_test_libcerror.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_memory.c fdatetime_test_memory.h \
	fdatetime_test_unused.h

fdatetime_test_floatingtime_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@

fdatetime_test_hfs_time_SOURCES = \
	fdatetime_test_hfs_time.c \
	fdatetime_test_libcerror.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_memory.c fdatetime_test_memory.h \
	fdatetime_test_unused.h

fdatetime_test_hfs_time_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@

fdatetime_test_nsf_timedate_SOURCES = \
	fdatetime_test_libcerror.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_memory.c fdatetime_test_memory.h \
	fdatetime_test_nsf_timedate.c \
	fdatetime_test_unused.h

fdatetime_test_nsf_timedate_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@

fdatetime_test_posix_time_SOURCES = \
	fdatetime_test_libcerror.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_memory.c fdatetime_test_memory.h \
	fdatetime_test_posix_time.c \
	fdatetime_test_unused.h

fdatetime_test_posix_time_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@

fdatetime_test_support_SOURCES = \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_support.c \
	fdatetime_test_unused.h

fdatetime_test_support_LDADD = \
	../libfdatetime/libfdatetime.la

fdatetime_test_systemtime_SOURCES = \
	fdatetime_test_libcerror.h \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_macros.h \
	fdatetime_test_memory.c fdatetime_test_memory.h \
	fdatetime_test_systemtime.c \
	fdatetime_test_unused.h

fdatetime_test_systemtime_LDADD = \
	../libfdatetime/libfdatetime.la \
	@LIBCERROR_LIBADD@

DISTCLEANFILES = \
	Makefile \
	Makefile.in

