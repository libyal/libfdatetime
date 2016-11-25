/*
 * Library SYSTEMTIME type testing program
 *
 * Copyright (C) 2009-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fdatetime_test_libfdatetime.h"
#include "fdatetime_test_libcerror.h"
#include "fdatetime_test_macros.h"
#include "fdatetime_test_memory.h"
#include "fdatetime_test_unused.h"

/* Tests the libfdatetime_systemtime_initialize function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_systemtime_initialize(
     void )
{
	libfdatetime_systemtime_t *systemtime = NULL;
	libcerror_error_t *error              = NULL;
	int result                            = 0;

	/* Test libfdatetime_systemtime_initialize without entries
	 */
	result = libfdatetime_systemtime_initialize(
	          &systemtime,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "systemtime",
         systemtime );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfdatetime_systemtime_free(
	          &systemtime,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "systemtime",
         systemtime );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfdatetime_systemtime_initialize(
	          NULL,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	systemtime = (libfdatetime_systemtime_t *) 0x12345678UL;

	result = libfdatetime_systemtime_initialize(
	          &systemtime,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	systemtime = NULL;

#if defined( HAVE_FDATETIME_TEST_MEMORY )

	/* Test libfdatetime_systemtime_initialize with malloc failing
	 */
	fdatetime_test_malloc_attempts_before_fail = 0;

	result = libfdatetime_systemtime_initialize(
	          &systemtime,
	          &error );

	if( fdatetime_test_malloc_attempts_before_fail != -1 )
	{
		fdatetime_test_malloc_attempts_before_fail = -1;
	}
	else
	{
		FDATETIME_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		FDATETIME_TEST_ASSERT_IS_NULL(
		 "systemtime",
		 systemtime );

		FDATETIME_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libfdatetime_systemtime_initialize with memset failing
	 */
	fdatetime_test_memset_attempts_before_fail = 0;

	result = libfdatetime_systemtime_initialize(
	          &systemtime,
	          &error );

	if( fdatetime_test_memset_attempts_before_fail != -1 )
	{
		fdatetime_test_memset_attempts_before_fail = -1;
	}
	else
	{
		FDATETIME_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		FDATETIME_TEST_ASSERT_IS_NULL(
		 "systemtime",
		 systemtime );

		FDATETIME_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_FDATETIME_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( systemtime != NULL )
	{
		libfdatetime_systemtime_free(
		 &systemtime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_systemtime_free function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_systemtime_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfdatetime_systemtime_free(
	          NULL,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfdatetime_systemtime_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_systemtime_copy_from_byte_stream(
     void )
{
	uint8_t byte_stream[ 16 ] = { 0xcf, 0x07, 0x0c, 0x00, 0x05, 0x00, 0x1f, 0x00, 0x17, 0x00, 0x3b, 0x00, 0x3b, 0x00, 0x00, 0x00 };

	libfdatetime_systemtime_t *systemtime = NULL;
	libcerror_error_t *error              = NULL;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_systemtime_initialize(
	          &systemtime,
	          &error );

	/* Test copy from byte stream
	 */
	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          byte_stream,
	          16,
	          LIBFDATETIME_ENDIAN_BIG,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          byte_stream,
	          16,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfdatetime_systemtime_copy_from_byte_stream(
	          NULL,
	          byte_stream,
	          16,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          NULL,
	          16,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          byte_stream,
	          8,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          byte_stream,
	          (size_t) SSIZE_MAX + 1,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          byte_stream,
	          16,
	          100,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdatetime_systemtime_free(
	          &systemtime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( systemtime != NULL )
	{
		libfdatetime_systemtime_free(
		 &systemtime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_systemtime_get_string_size function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_systemtime_get_string_size(
     void )
{
	uint8_t byte_stream[ 16 ] = { 0xcf, 0x07, 0x0c, 0x00, 0x05, 0x00, 0x1f, 0x00, 0x17, 0x00, 0x3b, 0x00, 0x3b, 0x00, 0x00, 0x00 };

	libfdatetime_systemtime_t *systemtime = NULL;
	libcerror_error_t *error              = NULL;
	size_t string_size                    = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_systemtime_initialize(
	          &systemtime,
	          &error );

	/* Test copy to string
	 */
	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          byte_stream,
	          16,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	result = libfdatetime_systemtime_get_string_size(
	          systemtime,
	          &string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "string_size",
	 string_size,
	 (size_t) 26 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          byte_stream,
	          16,
	          LIBFDATETIME_ENDIAN_BIG,
	          &error );

#ifdef TODO
	result = libfdatetime_systemtime_get_string_size(
	          systemtime,
	          &string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "string_size",
	 string_size,
	 (size_t) 57 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );
#endif

	/* Test error cases
	 */
	result = libfdatetime_systemtime_get_string_size(
	          NULL,
	          &string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_systemtime_get_string_size(
	          systemtime,
	          NULL,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdatetime_systemtime_free(
	          &systemtime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( systemtime != NULL )
	{
		libfdatetime_systemtime_free(
		 &systemtime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_systemtime_copy_to_utf8_string function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_systemtime_copy_to_utf8_string(
     void )
{
	uint8_t date_time_string[ 64 ];

	uint8_t byte_stream[ 16 ] = { 0xcf, 0x07, 0x0c, 0x00, 0x05, 0x00, 0x1f, 0x00, 0x17, 0x00, 0x3b, 0x00, 0x3b, 0x00, 0x00, 0x00 };

	libfdatetime_systemtime_t *systemtime = NULL;
	libcerror_error_t *error              = NULL;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_systemtime_initialize(
	          &systemtime,
	          &error );

	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          byte_stream,
	          16,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	/* Test copy to string
	 */
	result = libfdatetime_systemtime_copy_to_utf8_string(
	          systemtime,
	          date_time_string,
	          64,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfdatetime_systemtime_copy_to_utf8_string(
	          NULL,
	          date_time_string,
	          64,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdatetime_systemtime_free(
	          &systemtime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( systemtime != NULL )
	{
		libfdatetime_systemtime_free(
		 &systemtime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_systemtime_copy_to_utf8_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_systemtime_copy_to_utf8_string_with_index(
     void )
{
	uint8_t date_time_string[ 64 ];

	uint8_t byte_stream[ 16 ] = { 0xcf, 0x07, 0x0c, 0x00, 0x05, 0x00, 0x1f, 0x00, 0x17, 0x00, 0x3b, 0x00, 0x3b, 0x00, 0x00, 0x00 };

	libfdatetime_systemtime_t *systemtime = NULL;
	libcerror_error_t *error              = NULL;
	size_t string_index                   = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_systemtime_initialize(
	          &systemtime,
	          &error );

	/* Test copy to string with index
	 */
	string_index = 0;

	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          byte_stream,
	          16,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	result = libfdatetime_systemtime_copy_to_utf8_string_with_index(
	          systemtime,
	          date_time_string,
	          64,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = narrow_string_compare(
	          date_time_string,
	          "Dec 31, 1999 23:59:59.000",
	          25 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

#ifdef TODO
	string_index = 0;

	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          byte_stream,
	          16,
	          LIBFDATETIME_ENDIAN_BIG,
	          &error );

	result = libfdatetime_systemtime_copy_to_utf8_string_with_index(
	          systemtime,
	          date_time_string,
	          64,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = narrow_string_compare(
	          date_time_string,
	          "(0xce170a3d 0x623acb01)",
	          23 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );
#endif

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_systemtime_copy_to_utf8_string_with_index(
	          NULL,
	          date_time_string,
	          64,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

#ifdef TODO
	result = libfdatetime_systemtime_copy_to_utf8_string_with_index(
	          systemtime,
	          date_time_string,
	          56,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );
#endif

	/* Clean up
	 */
	result = libfdatetime_systemtime_free(
	          &systemtime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( systemtime != NULL )
	{
		libfdatetime_systemtime_free(
		 &systemtime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_systemtime_copy_to_utf16_string function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_systemtime_copy_to_utf16_string(
     void )
{
	uint16_t date_time_string[ 64 ];

	uint8_t byte_stream[ 16 ] = { 0xcf, 0x07, 0x0c, 0x00, 0x05, 0x00, 0x1f, 0x00, 0x17, 0x00, 0x3b, 0x00, 0x3b, 0x00, 0x00, 0x00 };

	libfdatetime_systemtime_t *systemtime = NULL;
	libcerror_error_t *error              = NULL;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_systemtime_initialize(
	          &systemtime,
	          &error );

	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          byte_stream,
	          16,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	/* Test copy to string
	 */
	result = libfdatetime_systemtime_copy_to_utf16_string(
	          systemtime,
	          date_time_string,
	          64,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfdatetime_systemtime_copy_to_utf16_string(
	          NULL,
	          date_time_string,
	          64,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdatetime_systemtime_free(
	          &systemtime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( systemtime != NULL )
	{
		libfdatetime_systemtime_free(
		 &systemtime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_systemtime_copy_to_utf16_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_systemtime_copy_to_utf16_string_with_index(
     void )
{
	uint16_t date_time_string[ 64 ];

	uint8_t byte_stream[ 16 ] = { 0xcf, 0x07, 0x0c, 0x00, 0x05, 0x00, 0x1f, 0x00, 0x17, 0x00, 0x3b, 0x00, 0x3b, 0x00, 0x00, 0x00 };

	libfdatetime_systemtime_t *systemtime = NULL;
	libcerror_error_t *error              = NULL;
	size_t string_index                   = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_systemtime_initialize(
	          &systemtime,
	          &error );

	/* Test copy to string with index
	 */
	string_index = 0;

	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          byte_stream,
	          16,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	result = libfdatetime_systemtime_copy_to_utf16_string_with_index(
	          systemtime,
	          date_time_string,
	          64,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

#ifdef TODO
	string_index = 0;

	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          byte_stream,
	          16,
	          LIBFDATETIME_ENDIAN_BIG,
	          &error );

	result = libfdatetime_systemtime_copy_to_utf16_string_with_index(
	          systemtime,
	          date_time_string,
	          64,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );
#endif

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_systemtime_copy_to_utf16_string_with_index(
	          NULL,
	          date_time_string,
	          64,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

#ifdef TODO
	result = libfdatetime_systemtime_copy_to_utf16_string_with_index(
	          systemtime,
	          date_time_string,
	          56,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );
#endif

	/* Clean up
	 */
	result = libfdatetime_systemtime_free(
	          &systemtime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( systemtime != NULL )
	{
		libfdatetime_systemtime_free(
		 &systemtime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_systemtime_copy_to_utf32_string function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_systemtime_copy_to_utf32_string(
     void )
{
	uint32_t date_time_string[ 64 ];

	uint8_t byte_stream[ 16 ] = { 0xcf, 0x07, 0x0c, 0x00, 0x05, 0x00, 0x1f, 0x00, 0x17, 0x00, 0x3b, 0x00, 0x3b, 0x00, 0x00, 0x00 };

	libfdatetime_systemtime_t *systemtime = NULL;
	libcerror_error_t *error              = NULL;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_systemtime_initialize(
	          &systemtime,
	          &error );

	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          byte_stream,
	          16,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	/* Test copy to string
	 */
	result = libfdatetime_systemtime_copy_to_utf32_string(
	          systemtime,
	          date_time_string,
	          64,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfdatetime_systemtime_copy_to_utf32_string(
	          NULL,
	          date_time_string,
	          64,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdatetime_systemtime_free(
	          &systemtime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( systemtime != NULL )
	{
		libfdatetime_systemtime_free(
		 &systemtime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_systemtime_copy_to_utf32_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_systemtime_copy_to_utf32_string_with_index(
     void )
{
	uint32_t date_time_string[ 64 ];

	uint8_t byte_stream[ 16 ] = { 0xcf, 0x07, 0x0c, 0x00, 0x05, 0x00, 0x1f, 0x00, 0x17, 0x00, 0x3b, 0x00, 0x3b, 0x00, 0x00, 0x00 };

	libfdatetime_systemtime_t *systemtime = NULL;
	libcerror_error_t *error              = NULL;
	size_t string_index                   = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_systemtime_initialize(
	          &systemtime,
	          &error );

	/* Test copy to string with index
	 */
	string_index = 0;

	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          byte_stream,
	          16,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	result = libfdatetime_systemtime_copy_to_utf32_string_with_index(
	          systemtime,
	          date_time_string,
	          64,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

#ifdef TODO
	string_index = 0;

	result = libfdatetime_systemtime_copy_from_byte_stream(
	          systemtime,
	          byte_stream,
	          16,
	          LIBFDATETIME_ENDIAN_BIG,
	          &error );

	result = libfdatetime_systemtime_copy_to_utf32_string_with_index(
	          systemtime,
	          date_time_string,
	          64,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );
#endif

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_systemtime_copy_to_utf32_string_with_index(
	          NULL,
	          date_time_string,
	          64,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

#ifdef TODO
	result = libfdatetime_systemtime_copy_to_utf32_string_with_index(
	          systemtime,
	          date_time_string,
	          56,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );
#endif

	/* Clean up
	 */
	result = libfdatetime_systemtime_free(
	          &systemtime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( systemtime != NULL )
	{
		libfdatetime_systemtime_free(
		 &systemtime,
		 NULL );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc FDATETIME_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] FDATETIME_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc FDATETIME_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] FDATETIME_TEST_ATTRIBUTE_UNUSED )
#endif
{
	FDATETIME_TEST_UNREFERENCED_PARAMETER( argc )
	FDATETIME_TEST_UNREFERENCED_PARAMETER( argv )

	FDATETIME_TEST_RUN(
	 "libfdatetime_systemtime_initialize",
	 fdatetime_test_systemtime_initialize );

	FDATETIME_TEST_RUN(
	 "libfdatetime_systemtime_free",
	 fdatetime_test_systemtime_free );

	FDATETIME_TEST_RUN(
	 "libfdatetime_systemtime_copy_from_byte_stream",
	 fdatetime_test_systemtime_copy_from_byte_stream );

	FDATETIME_TEST_RUN(
	 "libfdatetime_systemtime_get_string_size",
	 fdatetime_test_systemtime_get_string_size );

	FDATETIME_TEST_RUN(
	 "libfdatetime_systemtime_copy_to_utf8_string",
	 fdatetime_test_systemtime_copy_to_utf8_string );

	FDATETIME_TEST_RUN(
	 "libfdatetime_systemtime_copy_to_utf8_string_with_index",
	 fdatetime_test_systemtime_copy_to_utf8_string_with_index );

	FDATETIME_TEST_RUN(
	 "libfdatetime_systemtime_copy_to_utf16_string",
	 fdatetime_test_systemtime_copy_to_utf16_string );

	FDATETIME_TEST_RUN(
	 "libfdatetime_systemtime_copy_to_utf16_string_with_index",
	 fdatetime_test_systemtime_copy_to_utf16_string_with_index );

	FDATETIME_TEST_RUN(
	 "libfdatetime_systemtime_copy_to_utf32_string",
	 fdatetime_test_systemtime_copy_to_utf32_string );

	FDATETIME_TEST_RUN(
	 "libfdatetime_systemtime_copy_to_utf32_string_with_index",
	 fdatetime_test_systemtime_copy_to_utf32_string_with_index );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

