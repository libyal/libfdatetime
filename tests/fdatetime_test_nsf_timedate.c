/*
 * Library NSF timedate type testing program
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
#include "../libfdatetime/libfdatetime_nsf_timedate.h"

/* Tests the libfdatetime_nsf_timedate_initialize function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_nsf_timedate_initialize(
     void )
{
	libcerror_error_t *error                  = NULL;
	libfdatetime_nsf_timedate_t *nsf_timedate = NULL;
	int result                                = 0;

#if defined( HAVE_FDATETIME_TEST_MEMORY )
	int number_of_malloc_fail_tests           = 1;
	int number_of_memset_fail_tests           = 1;
	int test_number                           = 0;
#endif

	/* Test regular cases
	 */
	result = libfdatetime_nsf_timedate_initialize(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "nsf_timedate",
	 nsf_timedate );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_nsf_timedate_free(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "nsf_timedate",
	 nsf_timedate );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdatetime_nsf_timedate_initialize(
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

	nsf_timedate = (libfdatetime_nsf_timedate_t *) 0x12345678UL;

	result = libfdatetime_nsf_timedate_initialize(
	          &nsf_timedate,
	          &error );

	nsf_timedate = NULL;

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

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfdatetime_nsf_timedate_initialize with malloc failing
		 */
		fdatetime_test_malloc_attempts_before_fail = test_number;

		result = libfdatetime_nsf_timedate_initialize(
		          &nsf_timedate,
		          &error );

		if( fdatetime_test_malloc_attempts_before_fail != -1 )
		{
			fdatetime_test_malloc_attempts_before_fail = -1;

			if( nsf_timedate != NULL )
			{
				libfdatetime_nsf_timedate_free(
				 &nsf_timedate,
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
			 "nsf_timedate",
			 nsf_timedate );

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
		/* Test libfdatetime_nsf_timedate_initialize with memset failing
		 */
		fdatetime_test_memset_attempts_before_fail = test_number;

		result = libfdatetime_nsf_timedate_initialize(
		          &nsf_timedate,
		          &error );

		if( fdatetime_test_memset_attempts_before_fail != -1 )
		{
			fdatetime_test_memset_attempts_before_fail = -1;

			if( nsf_timedate != NULL )
			{
				libfdatetime_nsf_timedate_free(
				 &nsf_timedate,
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
			 "nsf_timedate",
			 nsf_timedate );

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
	if( nsf_timedate != NULL )
	{
		libfdatetime_nsf_timedate_free(
		 &nsf_timedate,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_nsf_timedate_free function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_nsf_timedate_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfdatetime_nsf_timedate_free(
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

/* Tests the libfdatetime_nsf_timedate_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_nsf_timedate_copy_from_byte_stream(
     void )
{
	uint8_t byte_stream[ 8 ] = { 0xf6, 0x32, 0x3b, 0x00, 0xb4, 0x72, 0x25, 0xc1 };

	libfdatetime_nsf_timedate_t *nsf_timedate = NULL;
	libcerror_error_t *error                  = NULL;
	int result                                = 0;

	/* Initialize test
	 */
	result = libfdatetime_nsf_timedate_initialize(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "nsf_timedate",
	 nsf_timedate );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	/* Test error cases
	 */
	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
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

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
	          byte_stream,
	          8,
	          -1,
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
	result = libfdatetime_nsf_timedate_free(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "nsf_timedate",
	 nsf_timedate );

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
	if( nsf_timedate != NULL )
	{
		libfdatetime_nsf_timedate_free(
		 &nsf_timedate,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_nsf_timedate_copy_from_64bit function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_nsf_timedate_copy_from_64bit(
     void )
{
	libfdatetime_nsf_timedate_t *nsf_timedate = NULL;
	libcerror_error_t *error                  = NULL;
	uint64_t value_64bit                      = 0xc12572b4003b32f6;
	int result                                = 0;

	/* Initialize test
	 */
	result = libfdatetime_nsf_timedate_initialize(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "nsf_timedate",
	 nsf_timedate );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdatetime_nsf_timedate_copy_from_64bit(
	          nsf_timedate,
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
	result = libfdatetime_nsf_timedate_copy_from_64bit(
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
	result = libfdatetime_nsf_timedate_free(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "nsf_timedate",
	 nsf_timedate );

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
	if( nsf_timedate != NULL )
	{
		libfdatetime_nsf_timedate_free(
		 &nsf_timedate,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_nsf_timedate_copy_to_64bit function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_nsf_timedate_copy_to_64bit(
     void )
{
	uint8_t byte_stream[ 8 ] = { 0xf6, 0x32, 0x3b, 0x00, 0xb4, 0x72, 0x25, 0xc1 };

	libfdatetime_nsf_timedate_t *nsf_timedate = NULL;
	libcerror_error_t *error                  = NULL;
	uint64_t value_64bit                      = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libfdatetime_nsf_timedate_initialize(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "nsf_timedate",
	 nsf_timedate );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	/* Test regular cases
	 */
	result = libfdatetime_nsf_timedate_copy_to_64bit(
	          nsf_timedate,
	          &value_64bit,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT64(
	 "value_64bit",
	 value_64bit,
	 0xc12572b4003b32f6 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdatetime_nsf_timedate_copy_to_64bit(
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

	result = libfdatetime_nsf_timedate_copy_to_64bit(
	          nsf_timedate,
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
	result = libfdatetime_nsf_timedate_free(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "nsf_timedate",
	 nsf_timedate );

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
	if( nsf_timedate != NULL )
	{
		libfdatetime_nsf_timedate_free(
		 &nsf_timedate,
		 NULL );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

/* Tests the libfdatetime_internal_nsf_timedate_copy_to_date_time_values function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_internal_nsf_timedate_copy_to_date_time_values(
     void )
{
	uint8_t byte_stream[ 8 ] = { 0xf6, 0x32, 0x3b, 0x00, 0xb4, 0x72, 0x25, 0xc1 };

	libcerror_error_t *error                          = NULL;
	libfdatetime_date_time_values_t *date_time_values = NULL;
	libfdatetime_nsf_timedate_t *nsf_timedate         = NULL;
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

	result = libfdatetime_nsf_timedate_initialize(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "nsf_timedate",
	 nsf_timedate );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	/* Test regular cases
	 */
	result = libfdatetime_internal_nsf_timedate_copy_to_date_time_values(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	          date_time_values,
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
	result = libfdatetime_internal_nsf_timedate_copy_to_date_time_values(
	          NULL,
	          date_time_values,
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

	result = libfdatetime_internal_nsf_timedate_copy_to_date_time_values(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
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
	result = libfdatetime_nsf_timedate_free(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "nsf_timedate",
	 nsf_timedate );

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( nsf_timedate != NULL )
	{
		libfdatetime_nsf_timedate_free(
		 &nsf_timedate,
		 NULL );
	}
	if( nsf_timedate != NULL )
	{
		libfdatetime_date_time_values_free(
		 &date_time_values,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

/* Tests the libfdatetime_nsf_timedate_get_string_size function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_nsf_timedate_get_string_size(
     void )
{
	uint8_t byte_stream[ 8 ] = { 0xf6, 0x32, 0x3b, 0x00, 0xb4, 0x72, 0x25, 0xc1 };

	libfdatetime_nsf_timedate_t *nsf_timedate = NULL;
	libcerror_error_t *error                  = NULL;
	size_t string_size                        = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libfdatetime_nsf_timedate_initialize(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "nsf_timedate",
	 nsf_timedate );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	result = libfdatetime_nsf_timedate_get_string_size(
	          nsf_timedate,
	          &string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_size",
	 string_size,
	 (size_t) 26 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	result = libfdatetime_nsf_timedate_get_string_size(
	          nsf_timedate,
	          &string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS,
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
	result = libfdatetime_nsf_timedate_get_string_size(
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

	result = libfdatetime_nsf_timedate_get_string_size(
	          nsf_timedate,
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
	result = libfdatetime_nsf_timedate_free(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "nsf_timedate",
	 nsf_timedate );

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
	if( nsf_timedate != NULL )
	{
		libfdatetime_nsf_timedate_free(
		 &nsf_timedate,
		 NULL );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

/* Tests the libfdatetime_internal_nsf_timedate_copy_to_utf8_string_in_hexadecimal function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_internal_nsf_timedate_copy_to_utf8_string_in_hexadecimal(
     void )
{
	uint8_t expected_utf8_string[ 24 ] = {
		'(', '0', 'x', 'f', '6', '3', '2', '3', 'b', '0', '0', ' ', '0', 'x', 'b', '4',
		'7', '2', '2', '5', 'c', '1', ')', 0 };

	uint8_t utf8_string[ 32 ];

	uint8_t byte_stream[ 8 ] = { 0xf6, 0x32, 0x3b, 0x00, 0xb4, 0x72, 0x25, 0xc1 };

	libcerror_error_t *error                  = NULL;
	libfdatetime_nsf_timedate_t *nsf_timedate = NULL;
	size_t string_index                       = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libfdatetime_nsf_timedate_initialize(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "nsf_timedate",
	 nsf_timedate );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	/* Test regular cases
	 */
	string_index = 0;

	result = libfdatetime_internal_nsf_timedate_copy_to_utf8_string_in_hexadecimal(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	          utf8_string,
	          32,
	          &string_index,
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
	          sizeof( uint8_t ) * 24 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_internal_nsf_timedate_copy_to_utf8_string_in_hexadecimal(
	          NULL,
	          utf8_string,
	          32,
	          &string_index,
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

	result = libfdatetime_internal_nsf_timedate_copy_to_utf8_string_in_hexadecimal(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	          NULL,
	          32,
	          &string_index,
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

	result = libfdatetime_internal_nsf_timedate_copy_to_utf8_string_in_hexadecimal(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	          utf8_string,
	          (size_t) SSIZE_MAX + 1,
	          &string_index,
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

	result = libfdatetime_internal_nsf_timedate_copy_to_utf8_string_in_hexadecimal(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	          utf8_string,
	          23,
	          &string_index,
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

	result = libfdatetime_internal_nsf_timedate_copy_to_utf8_string_in_hexadecimal(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	          utf8_string,
	          32,
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
	result = libfdatetime_nsf_timedate_free(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "nsf_timedate",
	 nsf_timedate );

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
	if( nsf_timedate != NULL )
	{
		libfdatetime_nsf_timedate_free(
		 &nsf_timedate,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

/* Tests the libfdatetime_nsf_timedate_copy_to_utf8_string function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_nsf_timedate_copy_to_utf8_string(
     void )
{
	uint8_t utf8_string[ 32 ];

	uint8_t byte_stream[ 8 ] = { 0xf6, 0x32, 0x3b, 0x00, 0xb4, 0x72, 0x25, 0xc1 };

	libfdatetime_nsf_timedate_t *nsf_timedate = NULL;
	libcerror_error_t *error                  = NULL;
	int result                                = 0;

	/* Initialize test
	 */
	result = libfdatetime_nsf_timedate_initialize(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "nsf_timedate",
	 nsf_timedate );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	/* Test regular cases
	 */
	result = libfdatetime_nsf_timedate_copy_to_utf8_string(
	          nsf_timedate,
	          utf8_string,
	          32,
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
	result = libfdatetime_nsf_timedate_copy_to_utf8_string(
	          NULL,
	          utf8_string,
	          32,
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
	result = libfdatetime_nsf_timedate_free(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "nsf_timedate",
	 nsf_timedate );

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
	if( nsf_timedate != NULL )
	{
		libfdatetime_nsf_timedate_free(
		 &nsf_timedate,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_nsf_timedate_copy_to_utf8_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_nsf_timedate_copy_to_utf8_string_with_index(
     void )
{
	uint8_t expected_utf8_string1[ 26 ] = {
		'A', 'p', 'r', ' ', '0', '5', ',', ' ', '2', '0', '0', '7', ' ', '1', '0', ':',
		'4', '6', ':', '3', '6', '.', '7', '0', '0', 0 };

	uint8_t expected_utf8_string2[ 24 ] = {
		'(', '0', 'x', 'f', '6', '3', '2', '3', 'b', '0', '0', ' ', '0', 'x', 'b', '4',
		'7', '2', '2', '5', 'c', '1', ')', 0 };

	uint8_t utf8_string[ 32 ];

	uint8_t byte_stream[ 8 ] = { 0xf6, 0x32, 0x3b, 0x00, 0xb4, 0x72, 0x25, 0xc1 };

	libfdatetime_nsf_timedate_t *nsf_timedate = NULL;
	libcerror_error_t *error                  = NULL;
	size_t string_index                       = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libfdatetime_nsf_timedate_initialize(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "nsf_timedate",
	 nsf_timedate );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	string_index = 0;

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	result = libfdatetime_nsf_timedate_copy_to_utf8_string_with_index(
	          nsf_timedate,
	          utf8_string,
	          32,
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

	result = memory_compare(
	          utf8_string,
	          expected_utf8_string1,
	          sizeof( uint8_t ) * 26 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	string_index = 0;

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	result = libfdatetime_nsf_timedate_copy_to_utf8_string_with_index(
	          nsf_timedate,
	          utf8_string,
	          32,
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

	result = memory_compare(
	          utf8_string,
	          expected_utf8_string2,
	          sizeof( uint8_t ) * 24 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_nsf_timedate_copy_to_utf8_string_with_index(
	          NULL,
	          utf8_string,
	          32,
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

	/* Clean up
	 */
	result = libfdatetime_nsf_timedate_free(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "nsf_timedate",
	 nsf_timedate );

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
	if( nsf_timedate != NULL )
	{
		libfdatetime_nsf_timedate_free(
		 &nsf_timedate,
		 NULL );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

/* Tests the libfdatetime_internal_nsf_timedate_copy_to_utf16_string_in_hexadecimal function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_internal_nsf_timedate_copy_to_utf16_string_in_hexadecimal(
     void )
{
	uint16_t expected_utf16_string[ 24 ] = {
		'(', '0', 'x', 'f', '6', '3', '2', '3', 'b', '0', '0', ' ', '0', 'x', 'b', '4',
		'7', '2', '2', '5', 'c', '1', ')', 0 };

	uint16_t utf16_string[ 32 ];

	uint8_t byte_stream[ 8 ] = { 0xf6, 0x32, 0x3b, 0x00, 0xb4, 0x72, 0x25, 0xc1 };

	libcerror_error_t *error                  = NULL;
	libfdatetime_nsf_timedate_t *nsf_timedate = NULL;
	size_t string_index                       = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libfdatetime_nsf_timedate_initialize(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "nsf_timedate",
	 nsf_timedate );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	/* Test regular cases
	 */
	string_index = 0;

	result = libfdatetime_internal_nsf_timedate_copy_to_utf16_string_in_hexadecimal(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	          utf16_string,
	          32,
	          &string_index,
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
	          sizeof( uint16_t ) * 24 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_internal_nsf_timedate_copy_to_utf16_string_in_hexadecimal(
	          NULL,
	          utf16_string,
	          32,
	          &string_index,
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

	result = libfdatetime_internal_nsf_timedate_copy_to_utf16_string_in_hexadecimal(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	          NULL,
	          32,
	          &string_index,
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

	result = libfdatetime_internal_nsf_timedate_copy_to_utf16_string_in_hexadecimal(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &string_index,
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

	result = libfdatetime_internal_nsf_timedate_copy_to_utf16_string_in_hexadecimal(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	          utf16_string,
	          23,
	          &string_index,
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

	result = libfdatetime_internal_nsf_timedate_copy_to_utf16_string_in_hexadecimal(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	          utf16_string,
	          32,
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
	result = libfdatetime_nsf_timedate_free(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "nsf_timedate",
	 nsf_timedate );

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
	if( nsf_timedate != NULL )
	{
		libfdatetime_nsf_timedate_free(
		 &nsf_timedate,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

/* Tests the libfdatetime_nsf_timedate_copy_to_utf16_string function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_nsf_timedate_copy_to_utf16_string(
     void )
{
	uint16_t utf16_string[ 32 ];

	uint8_t byte_stream[ 8 ] = { 0xf6, 0x32, 0x3b, 0x00, 0xb4, 0x72, 0x25, 0xc1 };

	libfdatetime_nsf_timedate_t *nsf_timedate = NULL;
	libcerror_error_t *error                  = NULL;
	int result                                = 0;

	/* Initialize test
	 */
	result = libfdatetime_nsf_timedate_initialize(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "nsf_timedate",
	 nsf_timedate );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	/* Test regular cases
	 */
	result = libfdatetime_nsf_timedate_copy_to_utf16_string(
	          nsf_timedate,
	          utf16_string,
	          32,
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
	result = libfdatetime_nsf_timedate_copy_to_utf16_string(
	          NULL,
	          utf16_string,
	          32,
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
	result = libfdatetime_nsf_timedate_free(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "nsf_timedate",
	 nsf_timedate );

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
	if( nsf_timedate != NULL )
	{
		libfdatetime_nsf_timedate_free(
		 &nsf_timedate,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_nsf_timedate_copy_to_utf16_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_nsf_timedate_copy_to_utf16_string_with_index(
     void )
{
	uint16_t expected_utf16_string1[ 26 ] = {
		'A', 'p', 'r', ' ', '0', '5', ',', ' ', '2', '0', '0', '7', ' ', '1', '0', ':',
		'4', '6', ':', '3', '6', '.', '7', '0', '0', 0 };

	uint16_t expected_utf16_string2[ 24 ] = {
		'(', '0', 'x', 'f', '6', '3', '2', '3', 'b', '0', '0', ' ', '0', 'x', 'b', '4',
		'7', '2', '2', '5', 'c', '1', ')', 0 };

	uint16_t utf16_string[ 32 ];

	uint8_t byte_stream[ 8 ] = { 0xf6, 0x32, 0x3b, 0x00, 0xb4, 0x72, 0x25, 0xc1 };

	libfdatetime_nsf_timedate_t *nsf_timedate = NULL;
	libcerror_error_t *error                  = NULL;
	size_t string_index                       = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libfdatetime_nsf_timedate_initialize(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "nsf_timedate",
	 nsf_timedate );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	string_index = 0;

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	result = libfdatetime_nsf_timedate_copy_to_utf16_string_with_index(
	          nsf_timedate,
	          utf16_string,
	          32,
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

	result = memory_compare(
	          utf16_string,
	          expected_utf16_string1,
	          sizeof( uint16_t ) * 26 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	string_index = 0;

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	result = libfdatetime_nsf_timedate_copy_to_utf16_string_with_index(
	          nsf_timedate,
	          utf16_string,
	          32,
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

	result = memory_compare(
	          utf16_string,
	          expected_utf16_string2,
	          sizeof( uint16_t ) * 24 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_nsf_timedate_copy_to_utf16_string_with_index(
	          NULL,
	          utf16_string,
	          32,
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

	/* Clean up
	 */
	result = libfdatetime_nsf_timedate_free(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "nsf_timedate",
	 nsf_timedate );

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
	if( nsf_timedate != NULL )
	{
		libfdatetime_nsf_timedate_free(
		 &nsf_timedate,
		 NULL );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

/* Tests the libfdatetime_internal_nsf_timedate_copy_to_utf32_string_in_hexadecimal function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_internal_nsf_timedate_copy_to_utf32_string_in_hexadecimal(
     void )
{
	uint32_t expected_utf32_string[ 24 ] = {
		'(', '0', 'x', 'f', '6', '3', '2', '3', 'b', '0', '0', ' ', '0', 'x', 'b', '4',
		'7', '2', '2', '5', 'c', '1', ')', 0 };

	uint32_t utf32_string[ 32 ];

	uint8_t byte_stream[ 8 ] = { 0xf6, 0x32, 0x3b, 0x00, 0xb4, 0x72, 0x25, 0xc1 };

	libcerror_error_t *error                  = NULL;
	libfdatetime_nsf_timedate_t *nsf_timedate = NULL;
	size_t string_index                       = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libfdatetime_nsf_timedate_initialize(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "nsf_timedate",
	 nsf_timedate );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	/* Test regular cases
	 */
	string_index = 0;

	result = libfdatetime_internal_nsf_timedate_copy_to_utf32_string_in_hexadecimal(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	          utf32_string,
	          32,
	          &string_index,
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
	          sizeof( uint32_t ) * 24 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_internal_nsf_timedate_copy_to_utf32_string_in_hexadecimal(
	          NULL,
	          utf32_string,
	          32,
	          &string_index,
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

	result = libfdatetime_internal_nsf_timedate_copy_to_utf32_string_in_hexadecimal(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	          NULL,
	          32,
	          &string_index,
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

	result = libfdatetime_internal_nsf_timedate_copy_to_utf32_string_in_hexadecimal(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	          utf32_string,
	          (size_t) SSIZE_MAX + 1,
	          &string_index,
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

	result = libfdatetime_internal_nsf_timedate_copy_to_utf32_string_in_hexadecimal(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	          utf32_string,
	          23,
	          &string_index,
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

	result = libfdatetime_internal_nsf_timedate_copy_to_utf32_string_in_hexadecimal(
	          (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	          utf32_string,
	          32,
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
	result = libfdatetime_nsf_timedate_free(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "nsf_timedate",
	 nsf_timedate );

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
	if( nsf_timedate != NULL )
	{
		libfdatetime_nsf_timedate_free(
		 &nsf_timedate,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

/* Tests the libfdatetime_nsf_timedate_copy_to_utf32_string function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_nsf_timedate_copy_to_utf32_string(
     void )
{
	uint32_t utf32_string[ 32 ];

	uint8_t byte_stream[ 8 ] = { 0xf6, 0x32, 0x3b, 0x00, 0xb4, 0x72, 0x25, 0xc1 };

	libfdatetime_nsf_timedate_t *nsf_timedate = NULL;
	libcerror_error_t *error                  = NULL;
	int result                                = 0;

	/* Initialize test
	 */
	result = libfdatetime_nsf_timedate_initialize(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "nsf_timedate",
	 nsf_timedate );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	/* Test regular cases
	 */
	result = libfdatetime_nsf_timedate_copy_to_utf32_string(
	          nsf_timedate,
	          utf32_string,
	          32,
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
	result = libfdatetime_nsf_timedate_copy_to_utf32_string(
	          NULL,
	          utf32_string,
	          32,
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
	result = libfdatetime_nsf_timedate_free(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "nsf_timedate",
	 nsf_timedate );

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
	if( nsf_timedate != NULL )
	{
		libfdatetime_nsf_timedate_free(
		 &nsf_timedate,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdatetime_nsf_timedate_copy_to_utf32_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_nsf_timedate_copy_to_utf32_string_with_index(
     void )
{
	uint32_t expected_utf32_string1[ 26 ] = {
		'A', 'p', 'r', ' ', '0', '5', ',', ' ', '2', '0', '0', '7', ' ', '1', '0', ':',
		'4', '6', ':', '3', '6', '.', '7', '0', '0', 0 };

	uint32_t expected_utf32_string2[ 24 ] = {
		'(', '0', 'x', 'f', '6', '3', '2', '3', 'b', '0', '0', ' ', '0', 'x', 'b', '4',
		'7', '2', '2', '5', 'c', '1', ')', 0 };

	uint32_t utf32_string[ 32 ];

	uint8_t byte_stream[ 8 ] = { 0xf6, 0x32, 0x3b, 0x00, 0xb4, 0x72, 0x25, 0xc1 };

	libfdatetime_nsf_timedate_t *nsf_timedate = NULL;
	libcerror_error_t *error                  = NULL;
	size_t string_index                       = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libfdatetime_nsf_timedate_initialize(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "nsf_timedate",
	 nsf_timedate );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	string_index = 0;

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	result = libfdatetime_nsf_timedate_copy_to_utf32_string_with_index(
	          nsf_timedate,
	          utf32_string,
	          32,
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

	result = memory_compare(
	          utf32_string,
	          expected_utf32_string1,
	          sizeof( uint32_t ) * 26 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	string_index = 0;

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
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

	result = libfdatetime_nsf_timedate_copy_to_utf32_string_with_index(
	          nsf_timedate,
	          utf32_string,
	          32,
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

	result = memory_compare(
	          utf32_string,
	          expected_utf32_string2,
	          sizeof( uint32_t ) * 24 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_nsf_timedate_copy_to_utf32_string_with_index(
	          NULL,
	          utf32_string,
	          32,
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

	/* Clean up
	 */
	result = libfdatetime_nsf_timedate_free(
	          &nsf_timedate,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "nsf_timedate",
	 nsf_timedate );

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
	if( nsf_timedate != NULL )
	{
		libfdatetime_nsf_timedate_free(
		 &nsf_timedate,
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
	 "libfdatetime_nsf_timedate_initialize",
	 fdatetime_test_nsf_timedate_initialize );

	FDATETIME_TEST_RUN(
	 "libfdatetime_nsf_timedate_free",
	 fdatetime_test_nsf_timedate_free );

	FDATETIME_TEST_RUN(
	 "libfdatetime_nsf_timedate_copy_from_byte_stream",
	 fdatetime_test_nsf_timedate_copy_from_byte_stream );

	FDATETIME_TEST_RUN(
	 "libfdatetime_nsf_timedate_copy_from_64bit",
	 fdatetime_test_nsf_timedate_copy_from_64bit );

	FDATETIME_TEST_RUN(
	 "libfdatetime_nsf_timedate_copy_to_64bit",
	 fdatetime_test_nsf_timedate_copy_to_64bit );

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

	FDATETIME_TEST_RUN(
	 "libfdatetime_internal_nsf_timedate_copy_to_date_time_values",
	 fdatetime_test_internal_nsf_timedate_copy_to_date_time_values );

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

	FDATETIME_TEST_RUN(
	 "libfdatetime_nsf_timedate_get_string_size",
	 fdatetime_test_nsf_timedate_get_string_size );

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

	FDATETIME_TEST_RUN(
	 "libfdatetime_internal_nsf_timedate_copy_to_utf8_string_in_hexadecimal",
	 fdatetime_test_internal_nsf_timedate_copy_to_utf8_string_in_hexadecimal );

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

	FDATETIME_TEST_RUN(
	 "libfdatetime_nsf_timedate_copy_to_utf8_string",
	 fdatetime_test_nsf_timedate_copy_to_utf8_string );

	FDATETIME_TEST_RUN(
	 "libfdatetime_nsf_timedate_copy_to_utf8_string_with_index",
	 fdatetime_test_nsf_timedate_copy_to_utf8_string_with_index );

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

	FDATETIME_TEST_RUN(
	 "libfdatetime_internal_nsf_timedate_copy_to_utf16_string_in_hexadecimal",
	 fdatetime_test_internal_nsf_timedate_copy_to_utf16_string_in_hexadecimal );

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

	FDATETIME_TEST_RUN(
	 "libfdatetime_nsf_timedate_copy_to_utf16_string",
	 fdatetime_test_nsf_timedate_copy_to_utf16_string );

	FDATETIME_TEST_RUN(
	 "libfdatetime_nsf_timedate_copy_to_utf16_string_with_index",
	 fdatetime_test_nsf_timedate_copy_to_utf16_string_with_index );

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

	FDATETIME_TEST_RUN(
	 "libfdatetime_internal_nsf_timedate_copy_to_utf32_string_in_hexadecimal",
	 fdatetime_test_internal_nsf_timedate_copy_to_utf32_string_in_hexadecimal );

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

	FDATETIME_TEST_RUN(
	 "libfdatetime_nsf_timedate_copy_to_utf32_string",
	 fdatetime_test_nsf_timedate_copy_to_utf32_string );

	FDATETIME_TEST_RUN(
	 "libfdatetime_nsf_timedate_copy_to_utf32_string_with_index",
	 fdatetime_test_nsf_timedate_copy_to_utf32_string_with_index );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

