AC_PREREQ( 2.59 )

AC_INIT(
 [libfdatetime],
 [20101127],
 [jbmetz@users.sourceforge.net])

AC_CONFIG_SRCDIR(
 [include/libfdatetime.h.in])

AM_INIT_AUTOMAKE([gnu 1.6])

AC_CONFIG_MACRO_DIR([m4])

dnl Check for host type
AC_CANONICAL_HOST

dnl Check for large file support
AC_SYS_LARGEFILE

dnl Check for configure arguments
LIBFDATETIME_TEST_ENABLE(
 [winapi],
 [winapi],
 [enable WINAPI support for cross-compilation],
 [no])

dnl Check for libtool DLL support
AC_LIBTOOL_WIN32_DLL

dnl Checks for programs
AC_PROG_CC
AC_PROG_GCC_TRADITIONAL
AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)

dnl Check for compiler language support
AC_C_CONST
AC_C_VOLATILE

dnl Check for headers
dnl Headers included in libfdatetime/types.h
AC_CHECK_HEADERS([sys/types.h inttypes.h stdint.h])

AS_IF(
 [test "x$ac_cv_header_sys_types_h" = xyes],
 [AC_SUBST(
  [HAVE_SYS_TYPES_H],
  [1])],
 [AC_SUBST(
  [HAVE_SYS_TYPES_H],
  [0])])

AS_IF(
 [test "x$ac_cv_header_inttypes_h" = xyes],
 [AC_SUBST(
  [HAVE_INTTYPES_H],
  [1])],
 [AC_SUBST(
  [HAVE_INTTYPES_H],
  [0])])

AS_IF(
 [test "x$ac_cv_header_stdint_h" = xyes],
 [AC_SUBST(
  [HAVE_STDINT_H],
  [1])],
 [AC_SUBST(
  [HAVE_STDINT_H],
  [0])])

dnl Headers included in common/common.h
AS_IF(
 [test "x$ac_cv_libfdatetime_enable_winapi" = xyes],
 [AC_CHECK_HEADERS([windows.h])

 AS_IF(
  [test "x$ac_cv_header_windows_h" = xno],
  [AC_MSG_FAILURE(
   [Missing header: windows.h header is required to compile with winapi support],
   [1]) ])
 ])

dnl Headers included in common/types.h
AC_CHECK_HEADERS([limits.h])

dnl Headers included in common/memory.h and libcstring/libcstring_narrow_string.h
AC_CHECK_HEADERS([stdlib.h string.h])

dnl Headers included in libcstring/libcstring_locale.c
AC_CHECK_HEADERS([langinfo.h locale.h])

dnl Headers included in liberror/liberror_error.c and libnotify/libnotify_print.c
AC_CHECK_HEADERS([stdarg.h])

AS_IF(
 [test "x$ac_cv_header_stdarg_h" != xyes],
 [AC_CHECK_HEADERS([varargs.h]) ])

AS_IF(
 [test "x$ac_cv_header_stdarg_h" != xyes && test "x$ac_cv_header_varargs_h" != xyes],
 [AC_MSG_FAILURE(
  [Missing headers: stdarg.h and varargs.h],
  [1]) ])

dnl Other headers

dnl Check for declarations and type definitions
AC_TYPE_OFF_T
AC_TYPE_SIZE_T

AC_CHECK_TYPE(
 [size32_t],
 [AC_SUBST(
  [HAVE_SIZE32_T],
  [1])],
 [AC_SUBST(
  [HAVE_SIZE32_T],
  [0])])

AC_CHECK_TYPE(
 [ssize32_t],
 [AC_SUBST(
  [HAVE_SSIZE32_T],
  [1])],
 [AC_SUBST(
  [HAVE_SSIZE32_T],
  [0])])

AC_CHECK_TYPE(
 [size64_t],
 [AC_SUBST(
  [HAVE_SIZE64_T],
  [1])],
 [AC_SUBST(
  [HAVE_SIZE64_T],
  [0])])

AC_CHECK_TYPE(
 [ssize64_t],
 [AC_SUBST(
  [HAVE_SSIZE64_T],
  [1])],
 [AC_SUBST(
  [HAVE_SSIZE64_T],
  [0])])

AC_CHECK_TYPE(
 [off64_t],
 [AC_SUBST(
  [HAVE_OFF64_T],
  [1])],
 [AC_SUBST(
  [HAVE_OFF64_T],
  [0])])

AC_CHECK_TYPE([ssize_t])

AC_CHECK_SIZEOF([off_t])
AC_CHECK_SIZEOF([size_t])

dnl Check for functions
dnl File stream functions used in common/file_stream.h
AC_CHECK_FUNCS(
 [fclose],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fclose],
  [1]) ])

AC_CHECK_FUNCS(
 [feof],
 [],
 [AC_MSG_FAILURE(
  [Missing function: feof],
  [1]) ])

AC_CHECK_FUNCS(
 [fgets],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fgets],
  [1]) ])

AC_CHECK_FUNCS(
 [fopen],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fopen],
  [1]) ])

AC_CHECK_FUNCS(
 [fread],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fread],
  [1]) ])

AC_CHECK_FUNCS(
 [fseeko],
 [],
 [AC_CHECK_FUNCS(
  [fseeko64],
  [],
  [AC_MSG_FAILURE(
   [Missing function: fseeko and fseeko64],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [fwrite],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fwrite],
  [1]) ])

AC_CHECK_FUNCS(
 [vfprintf],
 [],
 [AC_MSG_FAILURE(
  [Missing function: vfprintf],
  [1]) ])

dnl Memory functions used in common/memory.h
AC_CHECK_FUNCS(
 [free],
 [],
 [AC_MSG_FAILURE(
  [Missing function: free],
  [1]) ])

AC_CHECK_FUNCS(
 [malloc],
 [],
 [AC_MSG_FAILURE(
  [Missing function: malloc],
  [1]) ])

AC_CHECK_FUNCS(
 [memcmp],
 [],
 [AC_MSG_FAILURE(
  [Missing function: memcmp],
  [1]) ])

AC_CHECK_FUNCS(
 [memcpy],
 [],
 [AC_MSG_FAILURE(
  [Missing function: memcpy],
  [1]) ])

AC_CHECK_FUNCS(
 [memset],
 [],
 [AC_MSG_FAILURE(
  [Missing function: memset],
  [1]) ])

AC_CHECK_FUNCS(
 [realloc],
 [],
 [AC_MSG_FAILURE(
  [Missing function: realloc],
  [1]) ])

dnl Narrow character string functions used in libcstring/libcstring_narrow_string.h
AC_CHECK_FUNCS(
 [fgets],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fgets],
  [1]) ])

AC_CHECK_FUNCS(
 [memchr],
 [],
 [AC_CHECK_FUNCS(
  [strchr],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: memchr and strchr],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [memcmp],
 [],
 [AC_CHECK_FUNCS(
  [strncmp],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: memcmp and strncmp],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [memcpy],
 [],
 [AC_CHECK_FUNCS(
  [strncpy],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: memcpy and strncpy],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [memrchr],
 [AC_CHECK_DECLS(
  [memrchr],
  [ac_libfdatetime_have_memrchr=yes],
  [ac_libfdatetime_have_memrchr=no]) ],
 [ac_libfdatetime_have_memrchr=no])

AS_IF(
 [test "x$ac_libfdatetime_have_memrchr" = xno],
 [AC_CHECK_FUNCS(
  [strrchr],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strrchr and memrchr],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [snprintf],
 [],
 [AC_MSG_FAILURE(
  [Missing function: snprintf],
  [1]) ])

AC_CHECK_FUNCS(
 [sscanf],
 [],
 [AC_MSG_FAILURE(
  [Missing function: sscanf],
  [1]) ])

AC_CHECK_FUNCS(
 [strlen],
 [],
 [AC_MSG_FAILURE(
  [Missing function: strlen],
  [1]) ])

AC_CHECK_FUNCS(
 [strncasecmp],
 [],
 [AC_CHECK_FUNCS(
  [strcasecmp],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strncasecmp and strcasecmp],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [strstr],
 [],
 [AC_MSG_FAILURE(
  [Missing function: strstr],
  [1]) ])

AC_CHECK_FUNCS(
 [strtoll],
 [],
 [AC_CHECK_FUNCS(
  [atoll],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strtoll and atoll],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [strtoull],
 [],
 [AC_CHECK_FUNCS(
  [atoll],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strtoull and atoll],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [vsnprintf],
 [],
 [AC_MSG_FAILURE(
  [Missing function: vsnprintf],
  [1]) ])

dnl Check for printf conversion specifier support
LIBFDATETIME_CHECK_FUNC_PRINTF_JD
LIBFDATETIME_CHECK_FUNC_PRINTF_ZD

dnl Checks for libraries and library functions
dnl ac_libfdatetime_dummy is used to prevent AC_CHECK_LIB adding unnecessary -l<library> arguments

dnl Set memwatch support
ac_libfdatetime_have_memwatch=no

AS_IF(
 [test "x$ac_libfdatetime_have_memwatch" != xno ],
 [AC_SUBST(
  [MEMWATCH_CPPFLAGS],
  ["-DMEMWATCH -DMEMWATCH_STDIO"])
 AC_SUBST(
  [MEMWATCH_LIBADD],
  [../common/libmemwatch.la]) ])

AM_CONDITIONAL(
 [HAVE_MEMWATCH],
 [test "x$ac_libfdatetime_have_memwatch" != xno])

dnl Set additional compiler flags
CFLAGS="$CFLAGS -Wall";

dnl Have configure make the Makefiles
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([include/Makefile])
AC_CONFIG_FILES([common/Makefile])
AC_CONFIG_FILES([libcstring/Makefile])
AC_CONFIG_FILES([liberror/Makefile])
AC_CONFIG_FILES([libfdatetime/Makefile])
AC_CONFIG_FILES([manuals/Makefile])
AC_CONFIG_FILES([borlandc/Makefile])
AC_CONFIG_FILES([msvscpp/Makefile])
dnl Have configure make the include files
AC_CONFIG_FILES([include/libfdatetime.h])
AC_CONFIG_FILES([include/libfdatetime/definitions.h])
AC_CONFIG_FILES([include/libfdatetime/types.h])
AC_CONFIG_FILES([libfdatetime/libfdatetime_definitions.h])
dnl Have configure make distribution specific files
AC_CONFIG_FILES([common/types.h])
AC_CONFIG_FILES([libfdatetime.pc])
AC_CONFIG_FILES([libfdatetime.spec])
dnl Have configure write its configuration
AC_CONFIG_HEADERS([common/config.h])

AC_OUTPUT

