/*
 * Date and time library NSF timedate copy from testing program
 *
 * Copyright (C) 2009-2015, Joachim Metz <joachim.metz@gmail.com>
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

/* Tests copying a NSF timedate from a byte stream
 * Returns 1 if successful, 0 if not or -1 on error
 */
int fdatetime_test_identifier_copy_from_byte_stream(
     libfdatetime_nsf_timedate_t *nsf_timedate,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     uint8_t byte_order,
     int expected_result )
{
	libcerror_error_t *error      = NULL;
	const char *byte_order_string = "unknown";
	int result                    = 0;

	if( byte_order == LIBFDATETIME_ENDIAN_BIG )
	{
		byte_order_string = "big-endian";
	}
	else if( byte_order == LIBFDATETIME_ENDIAN_LITTLE )
	{
		byte_order_string = "little-endian";
	}
        fprintf(
         stdout,
         "Testing copying NSF timedate from byte stream: 0x%08" PRIjx " of size: %" PRIzd " and byte order: %s\t",
         (intptr_t) byte_stream,
         byte_stream_size,
         byte_order_string );

	result = libfdatetime_nsf_timedate_copy_from_byte_stream(
	          nsf_timedate,
	          byte_stream,
	          byte_stream_size,
	          byte_order,
	          &error );

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
	/* Case 1: byte stream is NULL, byte stream size is 8 and byte order is little-endian
	 * Expected result: -1
	 */
	if( fdatetime_test_identifier_copy_from_byte_stream(
	     nsf_timedate,
	     NULL,
	     8,
	     LIBFDATETIME_ENDIAN_LITTLE,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to NSF timedate.\n" );

		goto on_error;
	}
	/* Case 1: byte stream is a buffer, byte stream size is 8 and byte order is big-endian
	 * Expected result: 1
	 */
	if( fdatetime_test_identifier_copy_from_byte_stream(
	     nsf_timedate,
	     byte_stream,
	     8,
	     LIBFDATETIME_ENDIAN_BIG,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to NSF timedate.\n" );

		goto on_error;
	}
	/* Case 2: byte stream is a buffer, byte stream size is 8 and byte order is little-endian
	 * Expected result: 1
	 */
	if( fdatetime_test_identifier_copy_from_byte_stream(
	     nsf_timedate,
	     byte_stream,
	     8,
	     LIBFDATETIME_ENDIAN_LITTLE,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to NSF timedate.\n" );

		goto on_error;
	}
	/* Case 3: byte stream is a buffer, byte stream size is 8 and byte order is 'X'
	 * Expected result: -1
	 */
	if( fdatetime_test_identifier_copy_from_byte_stream(
	     nsf_timedate,
	     byte_stream,
	     8,
	     (uint8_t) 'X',
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to NSF timedate.\n" );

		goto on_error;
	}
	/* Case 4: byte stream is a buffer, byte stream size is 2 and byte order is little-endian
	 * Expected result: -1
	 */
	if( fdatetime_test_identifier_copy_from_byte_stream(
	     nsf_timedate,
	     byte_stream,
	     2,
	     LIBFDATETIME_ENDIAN_LITTLE,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to NSF timedate.\n" );

		goto on_error;
	}
	/* Case 5: byte stream is a buffer, byte stream size is 0 and byte order is little-endian
	 * Expected result: -1
	 */
	if( fdatetime_test_identifier_copy_from_byte_stream(
	     nsf_timedate,
	     byte_stream,
	     0,
	     LIBFDATETIME_ENDIAN_LITTLE,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to NSF timedate.\n" );

		goto on_error;
	}
	/* Case 6: byte stream is a buffer, byte stream size is -1 and byte order is little-endian
	 * Expected result: -1
	 */
	if( fdatetime_test_identifier_copy_from_byte_stream(
	     nsf_timedate,
	     byte_stream,
	     (size_t) -1,
	     LIBFDATETIME_ENDIAN_LITTLE,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to NSF timedate.\n" );

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

