AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBFDATETIME_DLL_IMPORT@

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages

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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_library: \
	package.m4 \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

