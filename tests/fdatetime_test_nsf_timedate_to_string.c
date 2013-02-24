/*
 * Date and time library NSF timedate to string testing program
 *
 * Copyright (c) 2009-2013, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "fdatetime_test_libcerror.h"
#include "fdatetime_test_libcstring.h"
#include "fdatetime_test_libfdatetime.h"

/* Tests copying a NSF timedate to a string
 * Returns 1 if successful, 0 if not or -1 on error
 */
int fdatetime_test_identifier_to_string(
     libfdatetime_nsf_timedate_t *nsf_timedate,
     libcstring_system_character_t *nsf_timedate_string,
     size_t nsf_timedate_string_size,
     int expected_result )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

        fprintf(
         stdout,
         "Testing copying NSF timedate to string: 0x%08" PRIjx " of size: %" PRIzd "\t",
         (intptr_t) nsf_timedate_string,
         nsf_timedate_string_size );

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfdatetime_nsf_timedate_copy_to_utf16_string(
		  nsf_timedate,
		  (uint16_t *) nsf_timedate_string,
		  nsf_timedate_string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MICRO_SECONDS,
		  &error );
#else
	result = libfdatetime_nsf_timedate_copy_to_utf8_string(
		  nsf_timedate,
		  (uint8_t *) nsf_timedate_string,
		  nsf_timedate_string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MICRO_SECONDS,
		  &error );
#endif
	if( result == expected_result )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( result == 1 )
	{
		fprintf(
		 stdout,
		 "NSF timedate\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 nsf_timedate_string );
	}
	if( result == -1 )
	{
		if( expected_result != -1 )
		{
			libcerror_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libcerror_error_free(
		 &error );
	}
	if( result == expected_result )
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	return( result );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
        libcstring_system_character_t nsf_timedate_string[ 32 ];

	uint8_t byte_stream[ 8 ] = { 0xf6, 0x32, 0x3b, 0x00, 0xb4, 0x72, 0x25, 0xc1 };

	libcerror_error_t *error                  = NULL;
	libfdatetime_nsf_timedate_t *nsf_timedate = NULL;

	if( argc != 1 )
	{
		fprintf(
		 stderr,
		 "This program does not take arguments.\n" );

		return( EXIT_FAILURE );
	}
	if( libfdatetime_nsf_timedate_initialize(
	     &nsf_timedate,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create NSF timedate.\n" );

		goto on_error;
	}
	if( libfdatetime_nsf_timedate_copy_from_byte_stream(
	     nsf_timedate,
	     byte_stream,
	     8,
	     LIBFDATETIME_ENDIAN_LITTLE,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to NSF timedate.\n" );

		goto on_error;
	}
	/* Case 1: string is NULL, string size is 32
	 * Expected result: -1
	 */
	if( fdatetime_test_identifier_to_string(
	     nsf_timedate,
	     NULL,
	     32,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy NSF timedate to string.\n" );

		goto on_error;
	}
	/* Case 2: string is a buffer, string size is 32
	 * Expected result: 1
	 */
	if( fdatetime_test_identifier_to_string(
	     nsf_timedate,
	     nsf_timedate_string,
	     32,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy NSF timedate to string.\n" );

		goto on_error;
	}
	/* Case 3: string is a buffer, string size is 0
	 * Expected result: -1
	 */
	if( fdatetime_test_identifier_to_string(
	     nsf_timedate,
	     nsf_timedate_string,
	     0,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy NSF timedate to string.\n" );

		goto on_error;
	}
	/* Case 4: string is a buffer, string size is 10
	 * Expected result: -1
	 */
	if( fdatetime_test_identifier_to_string(
	     nsf_timedate,
	     nsf_timedate_string,
	     10,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy NSF timedate to string.\n" );

		goto on_error;
	}
	if( libfdatetime_nsf_timedate_free(
	     &nsf_timedate,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free NSF timedate.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stderr );
		libcerror_error_free(
		 &error );
	}
	if( nsf_timedate != NULL )
	{
		libfdatetime_nsf_timedate_free(
		 &nsf_timedate,
		 NULL );
	}
	return( EXIT_FAILURE );
}

