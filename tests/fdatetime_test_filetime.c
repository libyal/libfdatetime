/*
 * Library FILETIME type testing program
 *
 * Copyright (C) 2009-2017, Joachim Metz <joachim.metz@gmail.com>
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

#include "fdatetime_test_libcerror.h"
#include "fdatetime_test_libfdatetime.h"
#include "fdatetime_test_macros.h"
#include "fdatetime_test_memory.h"
#include "fdatetime_test_unused.h"

/* Tests the libfdatetime_filetime_initialize function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_filetime_initialize(
     void )
{
	libcerror_error_t *error          = NULL;
	libfdatetime_filetime_t *filetime = NULL;
	int result                        = 0;

#if defined( HAVE_FDATETIME_TEST_MEMORY )
	int number_of_malloc_fail_tests   = 1;
	int number_of_memset_fail_tests   = 1;
	int test_number                   = 0;
#endif

	/* Test regular cases
	 */
	result = libfdatetime_filetime_initialize(
	          &filetime,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "filetime",
	 filetime );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_filetime_free(
	          &filetime,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "filetime",
	 filetime );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdatetime_filetime_initialize(
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

	filetime = (libfdatetime_filetime_t *) 0x12345678UL;

	result = libfdatetime_filetime_initialize(
	          &filetime,
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

	filetime = NULL;

#if defined( HAVE_FDATETIME_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfdatetime_filetime_initialize with malloc failing
		 */
		fdatetime_test_malloc_attempts_before_fail = test_number;

		result = libfdatetime_filetime_initialize(
		          &filetime,
		          &error );

		if( fdatetime_test_malloc_attempts_before_fail != -1 )
		{
			fdatetime_test_malloc_attempts_before_fail = -1;

			if( filetime != NULL )
			{
				libfdatetime_filetime_free(
				 &filetime,
				 NULL );
			}
		}
		else
		{
			FDATETIME_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			FDATETIME_TEST_ASSERT_IS_NULL(
			 "filetime",
			 filetime );

			FDATETIME_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libfdatetime_filetime_initialize with memset failing
		 */
		fdatetime_test_memset_attempts_before_fail = test_number;

		result = libfdatetime_filetime_initialize(
		          &filetime,
		          &error );

		if( fdatetime_test_memset_attempts_before_fail != -1 )
		{
			fdatetime_test_memset_attempts_before_fail = -1;

			if( filetime != NULL )
			{
				libfdatetime_filetime_free(
				 &filetime,
				 NULL );
			}
		}
		else
		{
			FDATETIME_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			FDATETIME_TEST_ASSERT_IS_NULL(
			 "filetime",
			 filetime );

			FDATETIME_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_FDATETIME_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_filetime_free function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_filetime_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfdatetime_filetime_free(
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

/* Tests the libfdatetime_filetime_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_filetime_copy_from_byte_stream(
     void )
{
	uint8_t byte_stream[ 8 ] = { 0xce, 0x17, 0x0a, 0x3d, 0x62, 0x3a, 0xcb, 0x01 };

	libfdatetime_filetime_t *filetime = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdatetime_filetime_initialize(
	          &filetime,
	          &error );

	/* Test copy from byte stream
	 */
	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          byte_stream,
	          8,
	          LIBFDATETIME_ENDIAN_BIG,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          byte_stream,
	          8,
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
	result = libfdatetime_filetime_copy_from_byte_stream(
	          NULL,
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

	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          NULL,
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

	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          byte_stream,
	          4,
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

	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
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

	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          byte_stream,
	          8,
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
	result = libfdatetime_filetime_free(
	          &filetime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_filetime_copy_from_64bit function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_filetime_copy_from_64bit(
     void )
{
	libfdatetime_filetime_t *filetime = NULL;
	libcerror_error_t *error          = NULL;
	uint64_t value_64bit              = 0x1cb3a623d0a17ce;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdatetime_filetime_initialize(
	          &filetime,
	          &error );

	/* Test copy from byte stream
	 */
	result = libfdatetime_filetime_copy_from_64bit(
	          filetime,
	          value_64bit,
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
	result = libfdatetime_filetime_copy_from_64bit(
	          NULL,
	          value_64bit,
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
	result = libfdatetime_filetime_free(
	          &filetime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_filetime_copy_to_64bit function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_filetime_copy_to_64bit(
     void )
{
	uint8_t byte_stream[ 8 ] = { 0xce, 0x17, 0x0a, 0x3d, 0x62, 0x3a, 0xcb, 0x01 };

	libfdatetime_filetime_t *filetime = NULL;
	libcerror_error_t *error          = NULL;
	uint64_t value_64bit              = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdatetime_filetime_initialize(
	          &filetime,
	          &error );

	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          byte_stream,
	          8,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	/* Test copy to byte stream
	 */
	result = libfdatetime_filetime_copy_to_64bit(
	          filetime,
	          &value_64bit,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT64(
	 "value_64bit",
	 value_64bit,
	 0x1cb3a623d0a17ce );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdatetime_filetime_copy_to_64bit(
	          NULL,
	          &value_64bit,
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

	result = libfdatetime_filetime_copy_to_64bit(
	          filetime,
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
	result = libfdatetime_filetime_free(
	          &filetime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_filetime_get_string_size function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_filetime_get_string_size(
     void )
{
	uint8_t byte_stream[ 8 ] = { 0xce, 0x17, 0x0a, 0x3d, 0x62, 0x3a, 0xcb, 0x01 };

	libfdatetime_filetime_t *filetime = NULL;
	libcerror_error_t *error          = NULL;
	size_t string_size                = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdatetime_filetime_initialize(
	          &filetime,
	          &error );

	/* Test copy to string
	 */
	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          byte_stream,
	          8,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	result = libfdatetime_filetime_get_string_size(
	          filetime,
	          &string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_size",
	 string_size,
	 (size_t) 32 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          byte_stream,
	          8,
	          LIBFDATETIME_ENDIAN_BIG,
	          &error );

	result = libfdatetime_filetime_get_string_size(
	          filetime,
	          &string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_size",
	 string_size,
	 (size_t) 24 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdatetime_filetime_get_string_size(
	          NULL,
	          &string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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

	result = libfdatetime_filetime_get_string_size(
	          filetime,
	          NULL,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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
	result = libfdatetime_filetime_free(
	          &filetime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_filetime_copy_to_utf8_string function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_filetime_copy_to_utf8_string(
     void )
{
	uint8_t date_time_string[ 32 ];

	uint8_t byte_stream[ 8 ] = { 0xce, 0x17, 0x0a, 0x3d, 0x62, 0x3a, 0xcb, 0x01 };

	libfdatetime_filetime_t *filetime = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdatetime_filetime_initialize(
	          &filetime,
	          &error );

	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          byte_stream,
	          8,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	/* Test copy to string
	 */
	result = libfdatetime_filetime_copy_to_utf8_string(
	          filetime,
	          date_time_string,
	          32,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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
	result = libfdatetime_filetime_copy_to_utf8_string(
	          NULL,
	          date_time_string,
	          32,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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
	result = libfdatetime_filetime_free(
	          &filetime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_filetime_copy_to_utf8_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_filetime_copy_to_utf8_string_with_index(
     void )
{
	uint8_t date_time_string[ 32 ];

	uint8_t byte_stream[ 8 ] = { 0xce, 0x17, 0x0a, 0x3d, 0x62, 0x3a, 0xcb, 0x01 };

	libfdatetime_filetime_t *filetime = NULL;
	libcerror_error_t *error          = NULL;
	size_t string_index               = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdatetime_filetime_initialize(
	          &filetime,
	          &error );

	/* Test copy to string with index
	 */
	string_index = 0;

	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          byte_stream,
	          8,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	result = libfdatetime_filetime_copy_to_utf8_string_with_index(
	          filetime,
	          date_time_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = narrow_string_compare(
	          date_time_string,
	          "Aug 12, 2010 21:06:31.546875000",
	          31 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	string_index = 0;

	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          byte_stream,
	          8,
	          LIBFDATETIME_ENDIAN_BIG,
	          &error );

	result = libfdatetime_filetime_copy_to_utf8_string_with_index(
	          filetime,
	          date_time_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_filetime_copy_to_utf8_string_with_index(
	          NULL,
	          date_time_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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

	result = libfdatetime_filetime_copy_to_utf8_string_with_index(
	          filetime,
	          date_time_string,
	          23,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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
	result = libfdatetime_filetime_free(
	          &filetime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_filetime_copy_to_utf16_string function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_filetime_copy_to_utf16_string(
     void )
{
	uint16_t date_time_string[ 32 ];

	uint8_t byte_stream[ 8 ] = { 0xce, 0x17, 0x0a, 0x3d, 0x62, 0x3a, 0xcb, 0x01 };

	libfdatetime_filetime_t *filetime = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdatetime_filetime_initialize(
	          &filetime,
	          &error );

	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          byte_stream,
	          8,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	/* Test copy to string
	 */
	result = libfdatetime_filetime_copy_to_utf16_string(
	          filetime,
	          date_time_string,
	          32,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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
	result = libfdatetime_filetime_copy_to_utf16_string(
	          NULL,
	          date_time_string,
	          32,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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
	result = libfdatetime_filetime_free(
	          &filetime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_filetime_copy_to_utf16_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_filetime_copy_to_utf16_string_with_index(
     void )
{
	uint16_t date_time_string[ 32 ];

	uint8_t byte_stream[ 8 ] = { 0xce, 0x17, 0x0a, 0x3d, 0x62, 0x3a, 0xcb, 0x01 };

	libfdatetime_filetime_t *filetime = NULL;
	libcerror_error_t *error          = NULL;
	size_t string_index               = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdatetime_filetime_initialize(
	          &filetime,
	          &error );

	/* Test copy to string with index
	 */
	string_index = 0;

	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          byte_stream,
	          8,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	result = libfdatetime_filetime_copy_to_utf16_string_with_index(
	          filetime,
	          date_time_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	string_index = 0;

	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          byte_stream,
	          8,
	          LIBFDATETIME_ENDIAN_BIG,
	          &error );

	result = libfdatetime_filetime_copy_to_utf16_string_with_index(
	          filetime,
	          date_time_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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

	result = libfdatetime_filetime_copy_to_utf16_string_with_index(
	          NULL,
	          date_time_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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

	result = libfdatetime_filetime_copy_to_utf16_string_with_index(
	          filetime,
	          date_time_string,
	          23,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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
	result = libfdatetime_filetime_free(
	          &filetime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_filetime_copy_to_utf32_string function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_filetime_copy_to_utf32_string(
     void )
{
	uint32_t date_time_string[ 32 ];

	uint8_t byte_stream[ 8 ] = { 0xce, 0x17, 0x0a, 0x3d, 0x62, 0x3a, 0xcb, 0x01 };

	libfdatetime_filetime_t *filetime = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdatetime_filetime_initialize(
	          &filetime,
	          &error );

	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          byte_stream,
	          8,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	/* Test copy to string
	 */
	result = libfdatetime_filetime_copy_to_utf32_string(
	          filetime,
	          date_time_string,
	          32,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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
	result = libfdatetime_filetime_copy_to_utf32_string(
	          NULL,
	          date_time_string,
	          32,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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
	result = libfdatetime_filetime_free(
	          &filetime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_filetime_copy_to_utf32_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_filetime_copy_to_utf32_string_with_index(
     void )
{
	uint32_t date_time_string[ 32 ];

	uint8_t byte_stream[ 8 ] = { 0xce, 0x17, 0x0a, 0x3d, 0x62, 0x3a, 0xcb, 0x01 };

	libfdatetime_filetime_t *filetime = NULL;
	libcerror_error_t *error          = NULL;
	size_t string_index               = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdatetime_filetime_initialize(
	          &filetime,
	          &error );

	/* Test copy to string with index
	 */
	string_index = 0;

	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          byte_stream,
	          8,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          &error );

	result = libfdatetime_filetime_copy_to_utf32_string_with_index(
	          filetime,
	          date_time_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	string_index = 0;

	result = libfdatetime_filetime_copy_from_byte_stream(
	          filetime,
	          byte_stream,
	          8,
	          LIBFDATETIME_ENDIAN_BIG,
	          &error );

	result = libfdatetime_filetime_copy_to_utf32_string_with_index(
	          filetime,
	          date_time_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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

	result = libfdatetime_filetime_copy_to_utf32_string_with_index(
	          NULL,
	          date_time_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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

	result = libfdatetime_filetime_copy_to_utf32_string_with_index(
	          filetime,
	          date_time_string,
	          23,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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
	result = libfdatetime_filetime_free(
	          &filetime,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
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
	 "libfdatetime_filetime_initialize",
	 fdatetime_test_filetime_initialize );

	FDATETIME_TEST_RUN(
	 "libfdatetime_filetime_free",
	 fdatetime_test_filetime_free );

	/* TODO: add test for libfdatetime_filetime_add */

	FDATETIME_TEST_RUN(
	 "libfdatetime_filetime_copy_from_byte_stream",
	 fdatetime_test_filetime_copy_from_byte_stream );

	FDATETIME_TEST_RUN(
	 "libfdatetime_filetime_copy_from_64bit",
	 fdatetime_test_filetime_copy_from_64bit );

	FDATETIME_TEST_RUN(
	 "libfdatetime_filetime_copy_to_64bit",
	 fdatetime_test_filetime_copy_to_64bit );

	FDATETIME_TEST_RUN(
	 "libfdatetime_filetime_get_string_size",
	 fdatetime_test_filetime_get_string_size );

	FDATETIME_TEST_RUN(
	 "libfdatetime_filetime_copy_to_utf8_string",
	 fdatetime_test_filetime_copy_to_utf8_string );

	FDATETIME_TEST_RUN(
	 "libfdatetime_filetime_copy_to_utf8_string_with_index",
	 fdatetime_test_filetime_copy_to_utf8_string_with_index );

	FDATETIME_TEST_RUN(
	 "libfdatetime_filetime_copy_to_utf16_string",
	 fdatetime_test_filetime_copy_to_utf16_string );

	FDATETIME_TEST_RUN(
	 "libfdatetime_filetime_copy_to_utf16_string_with_index",
	 fdatetime_test_filetime_copy_to_utf16_string_with_index );

	FDATETIME_TEST_RUN(
	 "libfdatetime_filetime_copy_to_utf32_string",
	 fdatetime_test_filetime_copy_to_utf32_string );

	FDATETIME_TEST_RUN(
	 "libfdatetime_filetime_copy_to_utf32_string_with_index",
	 fdatetime_test_filetime_copy_to_utf32_string_with_index );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

