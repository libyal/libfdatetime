/*
 * Library POSIX time type testing program
 *
 * Copyright (C) 2009-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include "../libfdatetime/libfdatetime_posix_time.h"

uint8_t fdatetime_test_posix_time_byte_stream_32bit[ 4 ] = {
	0x7f, 0x9c, 0x64, 0x4f };

uint8_t fdatetime_test_posix_time_byte_stream_32bit_invalid[ 4 ] = {
	0x80, 0x00, 0x00, 0x00 };

uint8_t fdatetime_test_posix_time_byte_stream_64bit[ 8 ] = {
	0x00, 0x00, 0x00, 0x00, 0x4f, 0x64, 0x9c, 0x7f };

uint8_t fdatetime_test_posix_time_byte_stream_64bit_invalid[ 8 ] = {
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

uint8_t fdatetime_test_posix_time_byte_stream_64bit_with_microseconds[ 8 ] = {
	0xc0, 0xdd, 0xf0, 0xf4, 0x70, 0xbb, 0x04, 0x00 };

uint8_t fdatetime_test_posix_time_byte_stream_64bit_with_nanoseconds[ 8 ] = {
	0x0e, 0xa2, 0xb3, 0x12, 0x55, 0x23, 0x52, 0x15 };

/* Tests the libfdatetime_posix_time_initialize function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_initialize(
     void )
{
	libcerror_error_t *error              = NULL;
	libfdatetime_posix_time_t *posix_time = NULL;
	int result                            = 0;

#if defined( HAVE_FDATETIME_TEST_MEMORY )
	int number_of_malloc_fail_tests       = 1;
	int number_of_memset_fail_tests       = 1;
	int test_number                       = 0;
#endif

	/* Test regular cases
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

	posix_time = NULL;

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
		/* Test libfdatetime_posix_time_initialize with malloc failing
		 */
		fdatetime_test_malloc_attempts_before_fail = test_number;

		result = libfdatetime_posix_time_initialize(
		          &posix_time,
		          &error );

		if( fdatetime_test_malloc_attempts_before_fail != -1 )
		{
			fdatetime_test_malloc_attempts_before_fail = -1;

			if( posix_time != NULL )
			{
				libfdatetime_posix_time_free(
				 &posix_time,
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
			 "posix_time",
			 posix_time );

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
		/* Test libfdatetime_posix_time_initialize with memset failing
		 */
		fdatetime_test_memset_attempts_before_fail = test_number;

		result = libfdatetime_posix_time_initialize(
		          &posix_time,
		          &error );

		if( fdatetime_test_memset_attempts_before_fail != -1 )
		{
			fdatetime_test_memset_attempts_before_fail = -1;

			if( posix_time != NULL )
			{
				libfdatetime_posix_time_free(
				 &posix_time,
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
			 "posix_time",
			 posix_time );

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
	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	int result                            = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          fdatetime_test_posix_time_byte_stream_32bit,
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

	FDATETIME_TEST_ASSERT_EQUAL_UINT64(
	 "posix_time->timestamp",
	 ( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp,
	 (uint64_t) 0x7f9c644fUL );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "posix_time->value_type",
	 ( (libfdatetime_internal_posix_time_t *) posix_time )->value_type,
	 (uint8_t) LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED );

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          fdatetime_test_posix_time_byte_stream_32bit,
	          4,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_SIGNED,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FDATETIME_TEST_ASSERT_EQUAL_UINT64(
	 "posix_time->timestamp",
	 ( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp,
	 (uint64_t) 0x4f649c7fUL );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "posix_time->value_type",
	 ( (libfdatetime_internal_posix_time_t *) posix_time )->value_type,
	 (uint8_t) LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_SIGNED );

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          fdatetime_test_posix_time_byte_stream_64bit,
	          8,
	          LIBFDATETIME_ENDIAN_BIG,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FDATETIME_TEST_ASSERT_EQUAL_UINT64(
	 "posix_time->timestamp",
	 ( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp,
	 (uint64_t) 0x4f649c7fUL );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "posix_time->value_type",
	 ( (libfdatetime_internal_posix_time_t *) posix_time )->value_type,
	 (uint8_t) LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED );

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          fdatetime_test_posix_time_byte_stream_64bit_with_microseconds,
	          8,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_MICRO_SECONDS_64BIT_SIGNED,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FDATETIME_TEST_ASSERT_EQUAL_UINT64(
	 "posix_time->timestamp",
	 ( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp,
	 (uint64_t) 0x4bb70f4f0ddc0UL );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "posix_time->value_type",
	 ( (libfdatetime_internal_posix_time_t *) posix_time )->value_type,
	 (uint8_t) LIBFDATETIME_POSIX_TIME_VALUE_TYPE_MICRO_SECONDS_64BIT_SIGNED );

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          fdatetime_test_posix_time_byte_stream_64bit_with_nanoseconds,
	          8,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_NANO_SECONDS_64BIT_SIGNED,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FDATETIME_TEST_ASSERT_EQUAL_UINT64(
	 "posix_time->timestamp",
	 ( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp,
	 (uint64_t) 0x1552235512b3a20eUL );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "posix_time->value_type",
	 ( (libfdatetime_internal_posix_time_t *) posix_time )->value_type,
	 (uint8_t) LIBFDATETIME_POSIX_TIME_VALUE_TYPE_NANO_SECONDS_64BIT_SIGNED );

	/* Test error cases
	 */
	result = libfdatetime_posix_time_copy_from_byte_stream(
	          NULL,
	          fdatetime_test_posix_time_byte_stream_32bit,
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
	          fdatetime_test_posix_time_byte_stream_32bit,
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
	          fdatetime_test_posix_time_byte_stream_32bit,
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
	          fdatetime_test_posix_time_byte_stream_64bit,
	          6,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED,
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
	          fdatetime_test_posix_time_byte_stream_32bit,
	          4,
	          -1,
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
	          fdatetime_test_posix_time_byte_stream_32bit,
	          4,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          0xff,
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
	          fdatetime_test_posix_time_byte_stream_32bit_invalid,
	          4,
	          LIBFDATETIME_ENDIAN_BIG,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_SIGNED,
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
	          fdatetime_test_posix_time_byte_stream_64bit_invalid,
	          8,
	          LIBFDATETIME_ENDIAN_BIG,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_SIGNED,
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
	int result                            = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	result = libfdatetime_posix_time_copy_from_32bit(
	          posix_time,
	          0xcc28b975UL,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FDATETIME_TEST_ASSERT_EQUAL_UINT64(
	 "posix_time->timestamp",
	 ( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp,
	 (uint64_t) 0xcc28b975UL );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "posix_time->value_type",
	 ( (libfdatetime_internal_posix_time_t *) posix_time )->value_type,
	 (uint8_t) LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED );

	/* Test error cases
	 */
	result = libfdatetime_posix_time_copy_from_32bit(
	          NULL,
	          0xcc28b975UL,
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

	result = libfdatetime_posix_time_copy_from_32bit(
	          posix_time,
	          0xcc28b975UL,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED,
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

	result = libfdatetime_posix_time_copy_from_32bit(
	          posix_time,
	          0x80000000UL,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_SIGNED,
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

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          fdatetime_test_posix_time_byte_stream_32bit,
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

	/* Test regular cases
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
	 (uint32_t) 0x4f649c7fUL );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "value_type",
	 value_type,
	 (uint8_t) LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED );

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

	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = 0xff;

	result = libfdatetime_posix_time_copy_to_32bit(
	          posix_time,
	          &value_32bit,
	          &value_type,
	          &error );

	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED;

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

/* Tests the libfdatetime_posix_time_copy_from_64bit function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_copy_from_64bit(
     void )
{
	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	int result                            = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	result = libfdatetime_posix_time_copy_from_64bit(
	          posix_time,
	          0x00000000cc28b975UL,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FDATETIME_TEST_ASSERT_EQUAL_UINT64(
	 "posix_time->timestamp",
	 ( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp,
	 (uint64_t) 0x00000000cc28b975UL );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "posix_time->value_type",
	 ( (libfdatetime_internal_posix_time_t *) posix_time )->value_type,
	 (uint8_t) LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED );

	/* Test error cases
	 */
	result = libfdatetime_posix_time_copy_from_64bit(
	          NULL,
	          0x00000000cc28b975UL,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED,
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

	result = libfdatetime_posix_time_copy_from_64bit(
	          posix_time,
	          0x00000000cc28b975UL,
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

	result = libfdatetime_posix_time_copy_from_64bit(
	          posix_time,
	          0x8000000000000000UL,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_SIGNED,
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

/* Tests the libfdatetime_posix_time_copy_to_64bit function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_copy_to_64bit(
     void )
{
	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	uint64_t value_64bit                  = 0;
	uint8_t value_type                    = 0;
	int result                            = 0;

	/* Initialize test
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

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          fdatetime_test_posix_time_byte_stream_64bit,
	          8,
	          LIBFDATETIME_ENDIAN_BIG,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED,
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
	result = libfdatetime_posix_time_copy_to_64bit(
	          posix_time,
	          &value_64bit,
	          &value_type,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT64(
	 "value_64bit",
	 value_64bit,
	 (uint64_t) 0x000000004f649c7fUL );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "value_type",
	 value_type,
	 (uint8_t) LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdatetime_posix_time_copy_to_64bit(
	          NULL,
	          &value_64bit,
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

	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = 0xff;

	result = libfdatetime_posix_time_copy_to_64bit(
	          posix_time,
	          &value_64bit,
	          &value_type,
	          &error );

	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED;

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_posix_time_copy_to_64bit(
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

	result = libfdatetime_posix_time_copy_to_64bit(
	          posix_time,
	          &value_64bit,
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

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

/* Tests the libfdatetime_internal_posix_time_copy_to_date_time_values function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_internal_posix_time_copy_to_date_time_values(
     void )
{
	libcerror_error_t *error                          = NULL;
	libfdatetime_date_time_values_t *date_time_values = NULL;
	libfdatetime_posix_time_t *posix_time             = NULL;
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

	/* Test regular cases
	 */
	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          fdatetime_test_posix_time_byte_stream_32bit,
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

	result = libfdatetime_internal_posix_time_copy_to_date_time_values(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          date_time_values,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "date_time_values->year",
	 date_time_values->year,
	 (uint16_t) 2012 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->month",
	 date_time_values->month,
	 (uint8_t) 3 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->day",
	 date_time_values->day,
	 (uint8_t) 17 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->hours",
	 date_time_values->hours,
	 (uint8_t) 14 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->minutes",
	 date_time_values->minutes,
	 (uint8_t) 15 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->seconds",
	 date_time_values->seconds,
	 (uint8_t) 27 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "date_time_values->milli_seconds",
	 date_time_values->milli_seconds,
	 (uint16_t) 0 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "date_time_values->micro_seconds",
	 date_time_values->micro_seconds,
	 (uint16_t) 0 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "date_time_values->nano_seconds",
	 date_time_values->nano_seconds,
	 (uint16_t) 0 );

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          fdatetime_test_posix_time_byte_stream_64bit,
	          8,
	          LIBFDATETIME_ENDIAN_BIG,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_internal_posix_time_copy_to_date_time_values(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          date_time_values,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "date_time_values->year",
	 date_time_values->year,
	 (uint16_t) 2012 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->month",
	 date_time_values->month,
	 (uint8_t) 3 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->day",
	 date_time_values->day,
	 (uint8_t) 17 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->hours",
	 date_time_values->hours,
	 (uint8_t) 14 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->minutes",
	 date_time_values->minutes,
	 (uint8_t) 15 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->seconds",
	 date_time_values->seconds,
	 (uint8_t) 27 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "date_time_values->milli_seconds",
	 date_time_values->milli_seconds,
	 (uint16_t) 0 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "date_time_values->micro_seconds",
	 date_time_values->micro_seconds,
	 (uint16_t) 0 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "date_time_values->nano_seconds",
	 date_time_values->nano_seconds,
	 (uint16_t) 0 );

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          fdatetime_test_posix_time_byte_stream_64bit_with_microseconds,
	          8,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_MICRO_SECONDS_64BIT_SIGNED,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_internal_posix_time_copy_to_date_time_values(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          date_time_values,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "date_time_values->year",
	 date_time_values->year,
	 (uint16_t) 2012 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->month",
	 date_time_values->month,
	 (uint8_t) 3 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->day",
	 date_time_values->day,
	 (uint8_t) 17 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->hours",
	 date_time_values->hours,
	 (uint8_t) 14 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->minutes",
	 date_time_values->minutes,
	 (uint8_t) 15 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->seconds",
	 date_time_values->seconds,
	 (uint8_t) 27 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "date_time_values->milli_seconds",
	 date_time_values->milli_seconds,
	 (uint16_t) 0 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "date_time_values->micro_seconds",
	 date_time_values->micro_seconds,
	 (uint16_t) 0 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "date_time_values->nano_seconds",
	 date_time_values->nano_seconds,
	 (uint16_t) 0 );

	result = libfdatetime_posix_time_copy_from_byte_stream(
	          posix_time,
	          fdatetime_test_posix_time_byte_stream_64bit_with_nanoseconds,
	          8,
	          LIBFDATETIME_ENDIAN_LITTLE,
	          LIBFDATETIME_POSIX_TIME_VALUE_TYPE_NANO_SECONDS_64BIT_SIGNED,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdatetime_internal_posix_time_copy_to_date_time_values(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          date_time_values,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "date_time_values->year",
	 date_time_values->year,
	 (uint16_t) 2018 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->month",
	 date_time_values->month,
	 (uint8_t) 9 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->day",
	 date_time_values->day,
	 (uint8_t) 7 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->hours",
	 date_time_values->hours,
	 (uint8_t) 14 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->minutes",
	 date_time_values->minutes,
	 (uint8_t) 7 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT8(
	 "date_time_values->seconds",
	 date_time_values->seconds,
	 (uint8_t) 51 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "date_time_values->milli_seconds",
	 date_time_values->milli_seconds,
	 (uint16_t) 179 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "date_time_values->micro_seconds",
	 date_time_values->micro_seconds,
	 (uint16_t) 715 );

	FDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "date_time_values->nano_seconds",
	 date_time_values->nano_seconds,
	 (uint16_t) 86 );

	/* Test error cases
	 */
	result = libfdatetime_internal_posix_time_copy_to_date_time_values(
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

	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = 0xff;

	result = libfdatetime_internal_posix_time_copy_to_date_time_values(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          date_time_values,
	          &error );

	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_MICRO_SECONDS_64BIT_SIGNED;

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_internal_posix_time_copy_to_date_time_values(
	          (libfdatetime_internal_posix_time_t *) posix_time,
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
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
	if( posix_time != NULL )
	{
		libfdatetime_date_time_values_free(
		 &date_time_values,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

/* Tests the libfdatetime_posix_time_get_string_size function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_get_string_size(
     void )
{
	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	size_t string_size                    = 0;
	int result                            = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4f649c7fUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED;

	result = libfdatetime_posix_time_get_string_size(
	          posix_time,
	          &string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_size",
	 string_size,
	 (size_t) 22 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = 0x80000000UL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_SIGNED;

	result = libfdatetime_posix_time_get_string_size(
	          posix_time,
	          &string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_size",
	 string_size,
	 (size_t) 13 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = 0x8000000000000000UL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_SIGNED;

	result = libfdatetime_posix_time_get_string_size(
	          posix_time,
	          &string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_size",
	 string_size,
	 (size_t) 21 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4f649c7fUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED;

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

	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = 0xff;

	result = libfdatetime_posix_time_get_string_size(
	          posix_time,
	          &string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED;

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

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

/* Tests the libfdatetime_internal_posix_time_copy_to_utf8_string_in_hexadecimal function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_internal_posix_time_copy_to_utf8_string_in_hexadecimal(
     void )
{
	uint8_t expected_utf8_string1[ 13 ] = {
		'(', '0', 'x', '4', 'f', '6', '4', '9', 'c', '7', 'f', ')', 0 };
	uint8_t expected_utf8_string2[ 21 ] = {
		'(', '0', 'x', '1', '5', '5', '2', '2', '3', '5', '5', '1', '2', 'b', '3', 'a',
                '2', '0', 'e', ')', 0 };

	uint8_t utf8_string[ 32 ];

	libcerror_error_t *error              = NULL;
	libfdatetime_posix_time_t *posix_time = NULL;
	size_t string_index                   = 0;
	int result                            = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4f649c7fUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED;

	string_index = 0;

	result = libfdatetime_internal_posix_time_copy_to_utf8_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf8_string,
	          32,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 13 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf8_string,
	          expected_utf8_string1,
	          sizeof( uint8_t ) * 13 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x1552235512b3a20e;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED;

	string_index = 0;

	result = libfdatetime_internal_posix_time_copy_to_utf8_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf8_string,
	          32,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 21 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf8_string,
	          expected_utf8_string2,
	          sizeof( uint8_t ) * 21 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_internal_posix_time_copy_to_utf8_string_in_hexadecimal(
	          NULL,
	          utf8_string,
	          32,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = 0xff;

	result = libfdatetime_internal_posix_time_copy_to_utf8_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf8_string,
	          32,
	          &string_index,
	          &error );

	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED;

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_internal_posix_time_copy_to_utf8_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          NULL,
	          32,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_internal_posix_time_copy_to_utf8_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf8_string,
	          (size_t) SSIZE_MAX + 1,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_internal_posix_time_copy_to_utf8_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf8_string,
	          12,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_internal_posix_time_copy_to_utf8_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf8_string,
	          32,
	          NULL,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
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

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

/* Tests the libfdatetime_posix_time_copy_to_utf8_string function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_copy_to_utf8_string(
     void )
{
	uint8_t utf8_string[ 32 ];

	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	int result                            = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4f649c7fUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED;

	result = libfdatetime_posix_time_copy_to_utf8_string(
	          posix_time,
	          utf8_string,
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
	          utf8_string,
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
	uint8_t expected_utf8_string1[ 22 ] = {
		'M', 'a', 'r', ' ', '1', '7', ',', ' ', '2', '0', '1', '2', ' ', '1', '4', ':',
		'1', '5', ':', '2', '7', 0 };

	uint8_t expected_utf8_string2[ 30 ] = {
		'2', '0', '1', '8', '-', '0', '9', '-', '0', '7', 'T', '1', '4', ':', '0', '7',
		':', '5', '1', '.', '1', '7', '9', '7', '1', '5', '0', '8', '6', 0 };

	uint8_t utf8_string[ 32 ];

	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	size_t string_index                   = 0;
	int result                            = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4f649c7fUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED;

	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf8_string_with_index(
	          posix_time,
	          utf8_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 22 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf8_string,
	          expected_utf8_string1,
	          sizeof( uint8_t ) * 22 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4f649c7fUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED;

	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf8_string_with_index(
	          posix_time,
	          utf8_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 22 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf8_string,
	          expected_utf8_string1,
	          sizeof( uint8_t ) * 22 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4bb70f4f0ddc0UL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_MICRO_SECONDS_64BIT_SIGNED;

	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf8_string_with_index(
	          posix_time,
	          utf8_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 22 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf8_string,
	          expected_utf8_string1,
	          sizeof( uint8_t ) * 22 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x1552235512b3a20eUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_NANO_SECONDS_64BIT_SIGNED;

	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf8_string_with_index(
	          posix_time,
	          utf8_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 30 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf8_string,
	          expected_utf8_string2,
	          sizeof( uint8_t ) * 30 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf8_string_with_index(
	          NULL,
	          utf8_string,
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

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

/* Tests the libfdatetime_internal_posix_time_copy_to_utf16_string_in_hexadecimal function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_internal_posix_time_copy_to_utf16_string_in_hexadecimal(
     void )
{
	uint16_t expected_utf16_string1[ 13 ] = {
		'(', '0', 'x', '4', 'f', '6', '4', '9', 'c', '7', 'f', ')', 0 };
	uint16_t expected_utf16_string2[ 21 ] = {
		'(', '0', 'x', '1', '5', '5', '2', '2', '3', '5', '5', '1', '2', 'b', '3', 'a',
                '2', '0', 'e', ')', 0 };

	uint16_t utf16_string[ 32 ];

	libcerror_error_t *error              = NULL;
	libfdatetime_posix_time_t *posix_time = NULL;
	size_t string_index                   = 0;
	int result                            = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4f649c7fUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED;

	string_index = 0;

	result = libfdatetime_internal_posix_time_copy_to_utf16_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf16_string,
	          32,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 13 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf16_string,
	          expected_utf16_string1,
	          sizeof( uint16_t ) * 13 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x1552235512b3a20e;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED;

	string_index = 0;

	result = libfdatetime_internal_posix_time_copy_to_utf16_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf16_string,
	          32,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 21 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf16_string,
	          expected_utf16_string2,
	          sizeof( uint16_t ) * 21 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_internal_posix_time_copy_to_utf16_string_in_hexadecimal(
	          NULL,
	          utf16_string,
	          32,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = 0xff;

	result = libfdatetime_internal_posix_time_copy_to_utf16_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf16_string,
	          32,
	          &string_index,
	          &error );

	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED;

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_internal_posix_time_copy_to_utf16_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          NULL,
	          32,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_internal_posix_time_copy_to_utf16_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
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

	result = libfdatetime_internal_posix_time_copy_to_utf16_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf16_string,
	          12,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_internal_posix_time_copy_to_utf16_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf16_string,
	          32,
	          NULL,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
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

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

/* Tests the libfdatetime_posix_time_copy_to_utf16_string function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_copy_to_utf16_string(
     void )
{
	uint16_t utf16_string[ 32 ];

	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	int result                            = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4f649c7fUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED;

	result = libfdatetime_posix_time_copy_to_utf16_string(
	          posix_time,
	          utf16_string,
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
	          utf16_string,
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
	uint16_t expected_utf16_string1[ 22 ] = {
		'M', 'a', 'r', ' ', '1', '7', ',', ' ', '2', '0', '1', '2', ' ', '1', '4', ':',
		'1', '5', ':', '2', '7', 0 };

	uint16_t expected_utf16_string2[ 30 ] = {
		'2', '0', '1', '8', '-', '0', '9', '-', '0', '7', 'T', '1', '4', ':', '0', '7',
		':', '5', '1', '.', '1', '7', '9', '7', '1', '5', '0', '8', '6', 0 };

	uint16_t utf16_string[ 32 ];

	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	size_t string_index                   = 0;
	int result                            = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4f649c7fUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED;

	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf16_string_with_index(
	          posix_time,
	          utf16_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 22 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf16_string,
	          expected_utf16_string1,
	          sizeof( uint16_t ) * 22 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4f649c7fUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED;

	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf16_string_with_index(
	          posix_time,
	          utf16_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 22 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf16_string,
	          expected_utf16_string1,
	          sizeof( uint16_t ) * 22 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4bb70f4f0ddc0UL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_MICRO_SECONDS_64BIT_SIGNED;

	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf16_string_with_index(
	          posix_time,
	          utf16_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 22 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf16_string,
	          expected_utf16_string1,
	          sizeof( uint16_t ) * 22 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x1552235512b3a20eUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_NANO_SECONDS_64BIT_SIGNED;

	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf16_string_with_index(
	          posix_time,
	          utf16_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 30 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf16_string,
	          expected_utf16_string2,
	          sizeof( uint16_t ) * 30 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf16_string_with_index(
	          NULL,
	          utf16_string,
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

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

/* Tests the libfdatetime_internal_posix_time_copy_to_utf32_string_in_hexadecimal function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_internal_posix_time_copy_to_utf32_string_in_hexadecimal(
     void )
{
	uint32_t expected_utf32_string1[ 13 ] = {
		'(', '0', 'x', '4', 'f', '6', '4', '9', 'c', '7', 'f', ')', 0 };
	uint32_t expected_utf32_string2[ 21 ] = {
		'(', '0', 'x', '1', '5', '5', '2', '2', '3', '5', '5', '1', '2', 'b', '3', 'a',
                '2', '0', 'e', ')', 0 };

	uint32_t utf32_string[ 32 ];

	libcerror_error_t *error              = NULL;
	libfdatetime_posix_time_t *posix_time = NULL;
	size_t string_index                   = 0;
	int result                            = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4f649c7fUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED;

	string_index = 0;

	result = libfdatetime_internal_posix_time_copy_to_utf32_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf32_string,
	          32,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 13 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf32_string,
	          expected_utf32_string1,
	          sizeof( uint32_t ) * 13 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x1552235512b3a20e;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED;

	string_index = 0;

	result = libfdatetime_internal_posix_time_copy_to_utf32_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf32_string,
	          32,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 21 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf32_string,
	          expected_utf32_string2,
	          sizeof( uint32_t ) * 21 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_internal_posix_time_copy_to_utf32_string_in_hexadecimal(
	          NULL,
	          utf32_string,
	          32,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = 0xff;

	result = libfdatetime_internal_posix_time_copy_to_utf32_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf32_string,
	          32,
	          &string_index,
	          &error );

	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED;

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_internal_posix_time_copy_to_utf32_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          NULL,
	          32,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_internal_posix_time_copy_to_utf32_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf32_string,
	          (size_t) SSIZE_MAX + 1,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_internal_posix_time_copy_to_utf32_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf32_string,
	          12,
	          &string_index,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdatetime_internal_posix_time_copy_to_utf32_string_in_hexadecimal(
	          (libfdatetime_internal_posix_time_t *) posix_time,
	          utf32_string,
	          32,
	          NULL,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 0 );

	FDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
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

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

/* Tests the libfdatetime_posix_time_copy_to_utf32_string function
 * Returns 1 if successful or 0 if not
 */
int fdatetime_test_posix_time_copy_to_utf32_string(
     void )
{
	uint32_t utf32_string[ 32 ];

	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	int result                            = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4f649c7fUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED;

	result = libfdatetime_posix_time_copy_to_utf32_string(
	          posix_time,
	          utf32_string,
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
	          utf32_string,
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
	uint32_t expected_utf32_string1[ 22 ] = {
		'M', 'a', 'r', ' ', '1', '7', ',', ' ', '2', '0', '1', '2', ' ', '1', '4', ':',
		'1', '5', ':', '2', '7', 0 };

	uint32_t expected_utf32_string2[ 30 ] = {
		'2', '0', '1', '8', '-', '0', '9', '-', '0', '7', 'T', '1', '4', ':', '0', '7',
		':', '5', '1', '.', '1', '7', '9', '7', '1', '5', '0', '8', '6', 0 };

	uint32_t utf32_string[ 32 ];

	libfdatetime_posix_time_t *posix_time = NULL;
	libcerror_error_t *error              = NULL;
	size_t string_index                   = 0;
	int result                            = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4f649c7fUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_UNSIGNED;

	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf32_string_with_index(
	          posix_time,
	          utf32_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 22 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf32_string,
	          expected_utf32_string1,
	          sizeof( uint32_t ) * 22 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4f649c7fUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_64BIT_UNSIGNED;

	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf32_string_with_index(
	          posix_time,
	          utf32_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 22 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf32_string,
	          expected_utf32_string1,
	          sizeof( uint32_t ) * 22 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x4bb70f4f0ddc0UL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_MICRO_SECONDS_64BIT_SIGNED;

	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf32_string_with_index(
	          posix_time,
	          utf32_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 22 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf32_string,
	          expected_utf32_string1,
	          sizeof( uint32_t ) * 22 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	( (libfdatetime_internal_posix_time_t *) posix_time )->timestamp  = (uint64_t) 0x1552235512b3a20eUL;
	( (libfdatetime_internal_posix_time_t *) posix_time )->value_type = LIBFDATETIME_POSIX_TIME_VALUE_TYPE_NANO_SECONDS_64BIT_SIGNED;

	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf32_string_with_index(
	          posix_time,
	          utf32_string,
	          32,
	          &string_index,
	          LIBFDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
	          &error );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATETIME_TEST_ASSERT_EQUAL_SIZE(
	 "string_index",
	 string_index,
	 (size_t) 30 );

	FDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          utf32_string,
	          expected_utf32_string2,
	          sizeof( uint32_t ) * 30 );

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	string_index = 0;

	result = libfdatetime_posix_time_copy_to_utf32_string_with_index(
	          NULL,
	          utf32_string,
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
	 "libfdatetime_posix_time_copy_from_64bit",
	 fdatetime_test_posix_time_copy_from_64bit );

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_copy_to_64bit",
	 fdatetime_test_posix_time_copy_to_64bit );

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

	FDATETIME_TEST_RUN(
	 "libfdatetime_internal_posix_time_copy_to_date_time_values",
	 fdatetime_test_internal_posix_time_copy_to_date_time_values );

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_get_string_size",
	 fdatetime_test_posix_time_get_string_size );

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

	FDATETIME_TEST_RUN(
	 "libfdatetime_internal_posix_time_copy_to_utf8_string_in_hexadecimal",
	 fdatetime_test_internal_posix_time_copy_to_utf8_string_in_hexadecimal );

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_copy_to_utf8_string",
	 fdatetime_test_posix_time_copy_to_utf8_string );

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_copy_to_utf8_string_with_index",
	 fdatetime_test_posix_time_copy_to_utf8_string_with_index );

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

	FDATETIME_TEST_RUN(
	 "libfdatetime_internal_posix_time_copy_to_utf16_string_in_hexadecimal",
	 fdatetime_test_internal_posix_time_copy_to_utf16_string_in_hexadecimal );

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_copy_to_utf16_string",
	 fdatetime_test_posix_time_copy_to_utf16_string );

	FDATETIME_TEST_RUN(
	 "libfdatetime_posix_time_copy_to_utf16_string_with_index",
	 fdatetime_test_posix_time_copy_to_utf16_string_with_index );

#if defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT )

	FDATETIME_TEST_RUN(
	 "libfdatetime_internal_posix_time_copy_to_utf32_string_in_hexadecimal",
	 fdatetime_test_internal_posix_time_copy_to_utf32_string_in_hexadecimal );

#endif /* defined( __GNUC__ ) && !defined( LIBFDATETIME_DLL_IMPORT ) */

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

