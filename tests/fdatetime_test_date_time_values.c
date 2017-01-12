/*
 * Library date_time_values type test program
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

#if defined( __GNUC__ )

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

	FDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	date_time_values = NULL;

#if defined( HAVE_FDATETIME_TEST_MEMORY )

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

#endif /* defined( __GNUC__ ) */

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

#if defined( __GNUC__ )

	FDATETIME_TEST_RUN(
	 "libfdatetime_date_time_values_initialize",
	 fdatetime_test_date_time_values_initialize );

	FDATETIME_TEST_RUN(
	 "libfdatetime_date_time_values_free",
	 fdatetime_test_date_time_values_free );

	/* TODO: add tests for libfdatetime_date_time_values_get_string_size */

	/* TODO: add tests for libfdatetime_date_time_values_copy_to_utf8_string_with_index */

	/* TODO: add tests for libfdatetime_date_time_values_copy_to_utf16_string_with_index */

	/* TODO: add tests for libfdatetime_date_time_values_copy_to_utf32_string_with_index */

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

