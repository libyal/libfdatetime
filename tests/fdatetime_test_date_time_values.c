/*
 * Library date_time_values type test program
 *
 * Copyright (C) 2009-2019, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fdatetime_test_libcerror.h"
#include "fdatetime_test_libfdatetime.h"
#include "fdatetime_test_macros.h"
#include "fdatetime_test_memory.h"
#include "fdatetime_test_unused.h"

#include "../libfdatetime/libfdatetime_date_time_values.h"

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

/* Tests the libfdatetime_date_time_values_initialize function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_date_time_values_initialize(
     void )
{
	libcerror_error_t *error                          = NULL;
	libfdatetime_date_time_values_t *date_time_values = NULL;
	int result                                        = 0;

#if defined( HAVE_FDATETIME_TEST_MEMORY )
	int number_of_malloc_fail_tests                   = 1;
	int number_of_memset_fail_tests                   = 1;
	int test_number                                   = 0;
#endif

	/* Test regular cases
	 */
	result = libfdatetime_date_time_values_initialize(
	          &date_time_values,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "date_time_values",
	 date_time_values );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_date_time_values_free(
	          &date_time_values,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "date_time_values",
	 date_time_values );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdatetime_date_time_values_initialize(
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

	date_time_values = (libfdatetime_date_time_values_t *) 0x12345678UL;

	result = libfdatetime_date_time_values_initialize(
	          &date_time_values,
	          &error );

	date_time_values = NULL;

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_FDATETIME_TEST_MEMORY )

	/* 1 fail in memory_allocate_structure
	 */
	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfdatetime_date_time_values_initialize with malloc failing
		 */
		fdatetime_test_malloc_attempts_before_fail = test_number;

		result = libfdatetime_date_time_values_initialize(
		          &date_time_values,
		          &error );

		if( fdatetime_test_malloc_attempts_before_fail != -1 )
		{
			fdatetime_test_malloc_attempts_before_fail = -1;

			if( date_time_values != NULL )
			{
				libfdatetime_date_time_values_free(
				 &date_time_values,
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
			 "date_time_values",
			 date_time_values );

			FDATETIME_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	/* 1 fail in memset after memory_allocate_structure
	 */
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libfdatetime_date_time_values_initialize with memset failing
		 */
		fdatetime_test_memset_attempts_before_fail = test_number;

		result = libfdatetime_date_time_values_initialize(
		          &date_time_values,
		          &error );

		if( fdatetime_test_memset_attempts_before_fail != -1 )
		{
			fdatetime_test_memset_attempts_before_fail = -1;

			if( date_time_values != NULL )
			{
				libfdatetime_date_time_values_free(
				 &date_time_values,
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
			 "date_time_values",
			 date_time_values );

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
	if( date_time_values != NULL )
	{
		libfdatetime_date_time_values_free(
		 &date_time_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_date_time_values_free function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_date_time_values_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfdatetime_date_time_values_free(
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

/* Tests the libfdatetime_date_time_values_get_string_size function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_date_time_values_get_string_size(
     void )
{
	libcerror_error_t *error                          = NULL;
	libfdatetime_date_time_values_t *date_time_values = NULL;
	size_t string_size                                = 0;
	int result                                        = 0;

	/* Initialize test
	 */
	result = libfdatetime_date_time_values_initialize(
	          &date_time_values,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "date_time_values",
	 date_time_values );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	date_time_values->year          = 2018;
	date_time_values->month         = 7;
	date_time_values->day           = 25;
	date_time_values->hours         = 8;
	date_time_values->minutes       = 49;
	date_time_values->seconds       = 51;
	date_time_values->milli_seconds = 123;
	date_time_values->micro_seconds = 456;
	date_time_values->nano_seconds  = 789;

	/* Test regular cases
	 */
	result = libfdatetime_date_time_values_get_string_size(
	          date_time_values,
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

	/* Test error cases
	 */
	result = libfdatetime_date_time_values_get_string_size(
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

	result = libfdatetime_date_time_values_get_string_size(
	          date_time_values,
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
	result = libfdatetime_date_time_values_free(
	          &date_time_values,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "date_time_values",
	 date_time_values );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( date_time_values != NULL )
	{
		libfdatetime_date_time_values_free(
		 &date_time_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_date_time_values_copy_to_utf8_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_date_time_values_copy_to_utf8_string_with_index(
     void )
{
	uint8_t expected_utf8_string[ 32 ] = {
		'J', 'u', 'l', ' ', '2', '5', ',', ' ', '2', '0', '1', '8', ' ', '0', '8', ':',
		'4', '9', ':', '5', '1', '.', '1', '2', '3', '4', '5', '6', '7', '8', '9', 0 };

	uint8_t utf8_string[ 32 ];

	libcerror_error_t *error                          = NULL;
	libfdatetime_date_time_values_t *date_time_values = NULL;
	size_t string_index                               = 0;
	int result                                        = 0;

	/* Initialize test
	 */
	result = libfdatetime_date_time_values_initialize(
	          &date_time_values,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "date_time_values",
	 date_time_values );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	date_time_values->year          = 2018;
	date_time_values->month         = 7;
	date_time_values->day           = 25;
	date_time_values->hours         = 8;
	date_time_values->minutes       = 49;
	date_time_values->seconds       = 51;
	date_time_values->milli_seconds = 123;
	date_time_values->micro_seconds = 456;
	date_time_values->nano_seconds  = 789;

	/* Test regular cases
	 */
	string_index = 0;

	result = libfdatetime_date_time_values_copy_to_utf8_string_with_index(
	          date_time_values,
	          utf8_string,
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

	result = memory_compare(
	          utf8_string,
	          expected_utf8_string,
	          sizeof( uint8_t ) * 32 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_date_time_values_copy_to_utf8_string_with_index(
	          NULL,
	          utf8_string,
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

	result = libfdatetime_date_time_values_copy_to_utf8_string_with_index(
	          date_time_values,
	          utf8_string,
	          31,
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
	result = libfdatetime_date_time_values_free(
	          &date_time_values,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "date_time_values",
	 date_time_values );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( date_time_values != NULL )
	{
		libfdatetime_date_time_values_free(
		 &date_time_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_date_time_values_copy_to_utf16_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_date_time_values_copy_to_utf16_string_with_index(
     void )
{
	uint16_t expected_utf16_string[ 32 ] = {
		'J', 'u', 'l', ' ', '2', '5', ',', ' ', '2', '0', '1', '8', ' ', '0', '8', ':',
		'4', '9', ':', '5', '1', '.', '1', '2', '3', '4', '5', '6', '7', '8', '9', 0 };

	uint16_t utf16_string[ 32 ];

	libcerror_error_t *error                          = NULL;
	libfdatetime_date_time_values_t *date_time_values = NULL;
	size_t string_index                               = 0;
	int result                                        = 0;

	/* Initialize test
	 */
	result = libfdatetime_date_time_values_initialize(
	          &date_time_values,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "date_time_values",
	 date_time_values );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	date_time_values->year          = 2018;
	date_time_values->month         = 7;
	date_time_values->day           = 25;
	date_time_values->hours         = 8;
	date_time_values->minutes       = 49;
	date_time_values->seconds       = 51;
	date_time_values->milli_seconds = 123;
	date_time_values->micro_seconds = 456;
	date_time_values->nano_seconds  = 789;

	/* Test regular cases
	 */
	string_index = 0;

	result = libfdatetime_date_time_values_copy_to_utf16_string_with_index(
	          date_time_values,
	          utf16_string,
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

	result = memory_compare(
	          utf16_string,
	          expected_utf16_string,
	          sizeof( uint16_t ) * 32 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_date_time_values_copy_to_utf16_string_with_index(
	          NULL,
	          utf16_string,
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

	result = libfdatetime_date_time_values_copy_to_utf16_string_with_index(
	          date_time_values,
	          utf16_string,
	          31,
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
	result = libfdatetime_date_time_values_free(
	          &date_time_values,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "date_time_values",
	 date_time_values );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( date_time_values != NULL )
	{
		libfdatetime_date_time_values_free(
		 &date_time_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_date_time_values_copy_to_utf32_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_date_time_values_copy_to_utf32_string_with_index(
     void )
{
	uint32_t expected_utf32_string[ 32 ] = {
		'J', 'u', 'l', ' ', '2', '5', ',', ' ', '2', '0', '1', '8', ' ', '0', '8', ':',
		'4', '9', ':', '5', '1', '.', '1', '2', '3', '4', '5', '6', '7', '8', '9', 0 };

	uint32_t utf32_string[ 32 ];

	libcerror_error_t *error                          = NULL;
	libfdatetime_date_time_values_t *date_time_values = NULL;
	size_t string_index                               = 0;
	int result                                        = 0;

	/* Initialize test
	 */
	result = libfdatetime_date_time_values_initialize(
	          &date_time_values,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "date_time_values",
	 date_time_values );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	date_time_values->year          = 2018;
	date_time_values->month         = 7;
	date_time_values->day           = 25;
	date_time_values->hours         = 8;
	date_time_values->minutes       = 49;
	date_time_values->seconds       = 51;
	date_time_values->milli_seconds = 123;
	date_time_values->micro_seconds = 456;
	date_time_values->nano_seconds  = 789;

	/* Test regular cases
	 */
	string_index = 0;

	result = libfdatetime_date_time_values_copy_to_utf32_string_with_index(
	          date_time_values,
	          utf32_string,
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

	result = memory_compare(
	          utf32_string,
	          expected_utf32_string,
	          sizeof( uint32_t ) * 32 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_date_time_values_copy_to_utf32_string_with_index(
	          NULL,
	          utf32_string,
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

	result = libfdatetime_date_time_values_copy_to_utf32_string_with_index(
	          date_time_values,
	          utf32_string,
	          31,
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
	result = libfdatetime_date_time_values_free(
	          &date_time_values,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "date_time_values",
	 date_time_values );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( date_time_values != NULL )
	{
		libfdatetime_date_time_values_free(
		 &date_time_values,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

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

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

	FDATETIME_TEST_RUN(
	 "libfdatetime_date_time_values_initialize",
	 fdatetime_test_date_time_values_initialize );

	FDATETIME_TEST_RUN(
	 "libfdatetime_date_time_values_free",
	 fdatetime_test_date_time_values_free );

	FDATETIME_TEST_RUN(
	 "libfdatetime_date_time_values_get_string_size",
	 fdatetime_test_date_time_values_get_string_size );

	FDATETIME_TEST_RUN(
	 "libfdatetime_date_time_values_copy_to_utf8_string_with_index",
	 fdatetime_test_date_time_values_copy_to_utf8_string_with_index );

	FDATETIME_TEST_RUN(
	 "libfdatetime_date_time_values_copy_to_utf16_string_with_index",
	 fdatetime_test_date_time_values_copy_to_utf16_string_with_index );

	FDATETIME_TEST_RUN(
	 "libfdatetime_date_time_values_copy_to_utf32_string_with_index",
	 fdatetime_test_date_time_values_copy_to_utf32_string_with_index );

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

