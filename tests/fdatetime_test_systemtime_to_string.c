/*
 * Date and time library systemtime to string testing program
 *
 * Copyright (c) 2009-2014, Joachim Metz <joachim.metz@gmail.com>
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

/* Tests copying a systemtime to a string
 * Returns 1 if successful, 0 if not or -1 on error
 */
int fdatetime_test_identifier_to_string(
     libfdatetime_systemtime_t *systemtime,
     libcstring_system_character_t *systemtime_string,
     size_t systemtime_string_size,
     int expected_result )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

        fprintf(
         stdout,
         "Testing copying systemtime to string: 0x%08" PRIjx " of size: %" PRIzd "\t",
         (intptr_t) systemtime_string,
         systemtime_string_size );

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfdatetime_systemtime_copy_to_utf16_string(
		  systemtime,
		  (uint16_t *) systemtime_string,
		  systemtime_string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		  &error );
#else
	result = libfdatetime_systemtime_copy_to_utf8_string(
		  systemtime,
		  (uint8_t *) systemtime_string,
		  systemtime_string_size,
	          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
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
		 "Systemtime\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 systemtime_string );
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
        libcstring_system_character_t systemtime_string[ 32 ];

	uint8_t byte_stream[ 16 ] = { 0xcf, 0x07, 0x0c, 0x00, 0x05, 0x00, 0x1f, 0x00, 0x17, 0x00, 0x3b, 0x00, 0x3b, 0x00, 0x00, 0x00 };

	libcerror_error_t *error              = NULL;
	libfdatetime_systemtime_t *systemtime = NULL;

	if( argc != 1 )
	{
		fprintf(
		 stderr,
		 "This program does not take arguments.\n" );

		return( EXIT_FAILURE );
	}
	if( libfdatetime_systemtime_initialize(
	     &systemtime,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create systemtime.\n" );

		goto on_error;
	}
	if( libfdatetime_systemtime_copy_from_byte_stream(
	     systemtime,
	     byte_stream,
	     16,
	     LIBFDATETIME_ENDIAN_LITTLE,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to systemtime.\n" );

		goto on_error;
	}
	/* Case 1: string is NULL, string size is 32
	 * Expected result: -1
	 */
	if( fdatetime_test_identifier_to_string(
	     systemtime,
	     NULL,
	     32,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy systemtime to string.\n" );

		goto on_error;
	}
	/* Case 2: string is a buffer, string size is 32
	 * Expected result: 1
	 */
	if( fdatetime_test_identifier_to_string(
	     systemtime,
	     systemtime_string,
	     32,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy systemtime to string.\n" );

		goto on_error;
	}
	/* Case 3: string is a buffer, string size is 0
	 * Expected result: -1
	 */
	if( fdatetime_test_identifier_to_string(
	     systemtime,
	     systemtime_string,
	     0,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy systemtime to string.\n" );

		goto on_error;
	}
	/* Case 4: string is a buffer, string size is 10
	 * Expected result: -1
	 */
	if( fdatetime_test_identifier_to_string(
	     systemtime,
	     systemtime_string,
	     10,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy systemtime to string.\n" );

		goto on_error;
	}
	if( libfdatetime_systemtime_free(
	     &systemtime,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free systemtime.\n" );

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
	if( systemtime != NULL )
	{
		libfdatetime_systemtime_free(
		 &systemtime,
		 NULL );
	}
	return( EXIT_FAILURE );
}

