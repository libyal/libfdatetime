/*
 * Library POSIX time type testing program
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

/* Tests the libfdatetime_posix_time_initialize function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_initialize(
     void )
{
	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	int result                            = 0;

	/* Test libfdatetime_posix_time_initialize without entries
	 */
	result = libfdatetime_posix_time_initialize(
	          &posix_time,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "posix_time",
         posix_time );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfdatetime_posix_time_free(
	          &posix_time,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "posix_time",
         posix_time );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfdatetime_posix_time_initialize(
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

	posix_time = (libfdatetime_posix_time_t *) 0x12345678UL;

	result = libfdatetime_posix_time_initialize(
	          &posix_time,
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

	posix_time = NULL;

#if defined( HAVE_FDATETIME_TEST_MEMORY )

	/* Test libfdatetime_posix_time_initialize with malloc failing
	 */
	fdatetime_test_malloc_attempts_before_fail = 0;

	result = libfdatetime_posix_time_initialize(
	          &posix_time,
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
		 "posix_time",
		 posix_time );

		FDATETIME_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libfdatetime_posix_time_initialize with memset failing
	 */
	fdatetime_test_memset_attempts_before_fail = 0;

	result = libfdatetime_posix_time_initialize(
	          &posix_time,
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
		 "posix_time",
		 posix_time );

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
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_posix_time_free function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfdatetime_posix_time_free(
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

/* Tests the libfdatetime_posix_time_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_copy_from_byte_stream(
     void )
{
	uint8_t byte_stream[ 4 ] = { 0x7f, 0x9c, 0x64, 0x4f };

	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_posix_time_initialize(
	          &posix_time,
	          &error );

	/* Test copy from byte stream
	 */
	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          byte_stream,
	          4,
	          LIBFDATETIME_ENDIAN_BIG,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          byte_stream,
	          4,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
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
	result = libfdatetime_posix_time_copy_from_byte_stream(
	          NULL,
	          byte_stream,
	          4,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
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

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          NULL,
	          4,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
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

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          byte_stream,
	          2,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
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

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          byte_stream,
	          (size_t) SSIZE_MAX + 1,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
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

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          byte_stream,
	          4,
	          100,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
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
	result = libfdatetime_posix_time_free(
	          &posix_time,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_posix_time_copy_from_32bit function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_copy_from_32bit(
     void )
{
	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	uint32_t value_32bit                  = 0xcc28b975;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_posix_time_initialize(
	          &posix_time,
	          &error );

	/* Test copy from byte stream
	 */
	result = libfdatetime_posix_time_copy_from_32bit(
	          posix_time,
	          value_32bit,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
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
	result = libfdatetime_posix_time_copy_from_32bit(
	          NULL,
	          value_32bit,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
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
	result = libfdatetime_posix_time_free(
	          &posix_time,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_posix_time_copy_to_32bit function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_copy_to_32bit(
     void )
{
	uint8_t byte_stream[ 4 ] = { 0x7f, 0x9c, 0x64, 0x4f };

	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	uint32_t value_32bit                  = 0;
	uint8_t value_type                    = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_posix_time_initialize(
	          &posix_time,
	          &error );

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          byte_stream,
	          4,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
	          &error );

	/* Test copy to byte stream
	 */
	result = libfdatetime_posix_time_copy_to_32bit(
	          posix_time,
	          &value_32bit,
	          &value_type,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT32(
	 "value_32bit",
	 value_32bit,
	 0x4f649c7f );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfdatetime_posix_time_copy_to_32bit(
	          NULL,
	          &value_32bit,
	          &value_type,
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

	result = libfdatetime_posix_time_copy_to_32bit(
	          posix_time,
	          NULL,
	          &value_type,
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

	result = libfdatetime_posix_time_copy_to_32bit(
	          posix_time,
	          &value_32bit,
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

	/* Clean up
	 */
	result = libfdatetime_posix_time_free(
	          &posix_time,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_posix_time_get_string_size function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_get_string_size(
     void )
{
	uint8_t byte_stream[ 4 ] = { 0x7f, 0x9c, 0x64, 0x4f };

	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	size_t string_size                    = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_posix_time_initialize(
	          &posix_time,
	          &error );

	/* Test copy to string
	 */
	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          byte_stream,
	          4,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
	          &error );

	result = libfdatetime_posix_time_get_string_size(
	          posix_time,
	          &string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "string_size",
	 string_size,
	 (size_t) 22 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfdatetime_posix_time_get_string_size(
	          NULL,
	          &string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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

	result = libfdatetime_posix_time_get_string_size(
	          posix_time,
	          NULL,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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
	result = libfdatetime_posix_time_free(
	          &posix_time,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_posix_time_copy_to_utf8_string function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_copy_to_utf8_string(
     void )
{
	uint8_t date_time_string[ 32 ];

	uint8_t byte_stream[ 4 ] = { 0x7f, 0x9c, 0x64, 0x4f };

	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_posix_time_initialize(
	          &posix_time,
	          &error );

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          byte_stream,
	          4,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
	          &error );

	/* Test copy to string
	 */
	result = libfdatetime_posix_time_copy_to_utf8_string(
	          posix_time,
	          date_time_string,
	          32,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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
	result = libfdatetime_posix_time_copy_to_utf8_string(
	          NULL,
	          date_time_string,
	          32,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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
	result = libfdatetime_posix_time_free(
	          &posix_time,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_posix_time_copy_to_utf8_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_copy_to_utf8_string_with_index(
     void )
{
	uint8_t date_time_string[ 32 ];

	uint8_t byte_stream[ 4 ] = { 0x7f, 0x9c, 0x64, 0x4f };

	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	size_t string_index                   = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_posix_time_initialize(
	          &posix_time,
	          &error );

	/* Test copy to string with index
	 */
	string_index = 0;

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          byte_stream,
	          4,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
	          &error );

	result = libfdatetime_posix_time_copy_to_utf8_string_with_index(
	          posix_time,
	          date_time_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = narrow_string_compare(
	          date_time_string,
	          "Mar 17, 2012 14:15:27",
	          21 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

        FDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf8_string_with_index(
	          NULL,
	          date_time_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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
	result = libfdatetime_posix_time_free(
	          &posix_time,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_posix_time_copy_to_utf16_string function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_copy_to_utf16_string(
     void )
{
	uint16_t date_time_string[ 32 ];

	uint8_t byte_stream[ 4 ] = { 0x7f, 0x9c, 0x64, 0x4f };

	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_posix_time_initialize(
	          &posix_time,
	          &error );

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          byte_stream,
	          4,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
	          &error );

	/* Test copy to string
	 */
	result = libfdatetime_posix_time_copy_to_utf16_string(
	          posix_time,
	          date_time_string,
	          32,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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
	result = libfdatetime_posix_time_copy_to_utf16_string(
	          NULL,
	          date_time_string,
	          32,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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
	result = libfdatetime_posix_time_free(
	          &posix_time,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_posix_time_copy_to_utf16_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_copy_to_utf16_string_with_index(
     void )
{
	uint16_t date_time_string[ 32 ];

	uint8_t byte_stream[ 4 ] = { 0x7f, 0x9c, 0x64, 0x4f };

	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	size_t string_index                   = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_posix_time_initialize(
	          &posix_time,
	          &error );

	/* Test copy to string with index
	 */
	string_index = 0;

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          byte_stream,
	          4,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
	          &error );

	result = libfdatetime_posix_time_copy_to_utf16_string_with_index(
	          posix_time,
	          date_time_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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
	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf16_string_with_index(
	          NULL,
	          date_time_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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
	result = libfdatetime_posix_time_free(
	          &posix_time,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_posix_time_copy_to_utf32_string function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_copy_to_utf32_string(
     void )
{
	uint32_t date_time_string[ 32 ];

	uint8_t byte_stream[ 4 ] = { 0x7f, 0x9c, 0x64, 0x4f };

	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_posix_time_initialize(
	          &posix_time,
	          &error );

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          byte_stream,
	          4,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
	          &error );

	/* Test copy to string
	 */
	result = libfdatetime_posix_time_copy_to_utf32_string(
	          posix_time,
	          date_time_string,
	          32,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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
	result = libfdatetime_posix_time_copy_to_utf32_string(
	          NULL,
	          date_time_string,
	          32,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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
	result = libfdatetime_posix_time_free(
	          &posix_time,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_posix_time_copy_to_utf32_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_copy_to_utf32_string_with_index(
     void )
{
	uint32_t date_time_string[ 32 ];

	uint8_t byte_stream[ 4 ] = { 0x7f, 0x9c, 0x64, 0x4f };

	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	size_t string_index                   = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdatetime_posix_time_initialize(
	          &posix_time,
	          &error );

	/* Test copy to string with index
	 */
	string_index = 0;

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          byte_stream,
	          4,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
	          &error );

	result = libfdatetime_posix_time_copy_to_utf32_string_with_index(
	          posix_time,
	          date_time_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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
	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf32_string_with_index(
	          NULL,
	          date_time_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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
	result = libfdatetime_posix_time_free(
	          &posix_time,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
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
	 "libfdatetime_posix_time_initialize",
	 fdatetime_test_posix_time_initialize );

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_free",
	 fdatetime_test_posix_time_free );

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_copy_from_byte_stream",
	 fdatetime_test_posix_time_copy_from_byte_stream );

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_copy_from_32bit",
	 fdatetime_test_posix_time_copy_from_32bit );

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_copy_to_32bit",
	 fdatetime_test_posix_time_copy_to_32bit );

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_get_string_size",
	 fdatetime_test_posix_time_get_string_size );

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_copy_to_utf8_string",
	 fdatetime_test_posix_time_copy_to_utf8_string );

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_copy_to_utf8_string_with_index",
	 fdatetime_test_posix_time_copy_to_utf8_string_with_index );

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_copy_to_utf16_string",
	 fdatetime_test_posix_time_copy_to_utf16_string );

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_copy_to_utf16_string_with_index",
	 fdatetime_test_posix_time_copy_to_utf16_string_with_index );

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_copy_to_utf32_string",
	 fdatetime_test_posix_time_copy_to_utf32_string );

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_copy_to_utf32_string_with_index",
	 fdatetime_test_posix_time_copy_to_utf32_string_with_index );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

