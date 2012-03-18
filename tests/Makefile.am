AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/libcstring \
	@MEMWATCH_CPPFLAGS@

TESTS = \
	test_fat_date_time_copy_from.sh \
	test_fat_date_time_to_string.sh \
	test_filetime_copy_from.sh \
	test_filetime_to_string.sh \
	test_nsf_timedate_copy_from.sh \
	test_nsf_timedate_to_string.sh
	test_posix_time_copy_from.sh \
	test_posix_time_to_string.sh

check_SCRIPTS = \
	test_fat_date_time_copy_from.sh \
	test_fat_date_time_to_string.sh \
	test_filetime_copy_from.sh \
	test_filetime_to_string.sh \
	test_nsf_timedate_copy_from.sh \
	test_nsf_timedate_to_string.sh
	test_posix_time_copy_from.sh \
	test_posix_time_to_string.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fdatetime_test_fat_date_time_copy_from \
	fdatetime_test_fat_date_time_to_string \
	fdatetime_test_filetime_copy_from \
	fdatetime_test_filetime_to_string \
	fdatetime_test_nsf_timedate_copy_from \
	fdatetime_test_nsf_timedate_to_string \
	fdatetime_test_posix_time_copy_from \
	fdatetime_test_posix_time_to_string

fdatetime_test_fat_date_time_copy_from_SOURCES = \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_fat_date_time_copy_from.c

fdatetime_test_fat_date_time_copy_from_LDADD = \
	../libcstring/libcstring.la \
	../libfdatetime/libfdatetime.la \
        @MEMWATCH_LIBADD@

fdatetime_test_fat_date_time_to_string_SOURCES = \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_fat_date_time_to_string.c

fdatetime_test_fat_date_time_to_string_LDADD = \
	../libcstring/libcstring.la \
	../libfdatetime/libfdatetime.la \
        @MEMWATCH_LIBADD@

fdatetime_test_filetime_copy_from_SOURCES = \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_filetime_copy_from.c

fdatetime_test_filetime_copy_from_LDADD = \
	../libcstring/libcstring.la \
	../libfdatetime/libfdatetime.la \
        @MEMWATCH_LIBADD@

fdatetime_test_filetime_to_string_SOURCES = \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_filetime_to_string.c

fdatetime_test_filetime_to_string_LDADD = \
	../libcstring/libcstring.la \
	../libfdatetime/libfdatetime.la \
        @MEMWATCH_LIBADD@

fdatetime_test_nsf_timedate_copy_from_SOURCES = \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_nsf_timedate_copy_from.c

fdatetime_test_nsf_timedate_copy_from_LDADD = \
	../libcstring/libcstring.la \
	../libfdatetime/libfdatetime.la \
        @MEMWATCH_LIBADD@

fdatetime_test_nsf_timedate_to_string_SOURCES = \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_nsf_timedate_to_string.c

fdatetime_test_nsf_timedate_to_string_LDADD = \
	../libcstring/libcstring.la \
	../libfdatetime/libfdatetime.la \
        @MEMWATCH_LIBADD@

fdatetime_test_posix_time_copy_from_SOURCES = \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_posix_time_copy_from.c

fdatetime_test_posix_time_copy_from_LDADD = \
	../libcstring/libcstring.la \
	../libfdatetime/libfdatetime.la \
        @MEMWATCH_LIBADD@

fdatetime_test_posix_time_to_string_SOURCES = \
	fdatetime_test_libfdatetime.h \
	fdatetime_test_posix_time_to_string.c

fdatetime_test_posix_time_to_string_LDADD = \
	../libcstring/libcstring.la \
	../libfdatetime/libfdatetime.la \
        @MEMWATCH_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

