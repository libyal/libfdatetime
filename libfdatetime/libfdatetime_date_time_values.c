/*
 * Date and time values functions
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
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
#include <memory.h>
#include <types.h>

#include <liberror.h>

#include "libfdatetime_definitions.h"
#include "libfdatetime_date_time_values.h"
#include "libfdatetime_string.h"
#include "libfdatetime_types.h"

/* Converts the date and time values into a string
 * The strings is encoded in UTF-8
 * The string size should include the end of string character
 * Returns 1 if successful, 0 if the date and time values are not a valid or -1 on error
 */
int libfdatetime_date_time_values_copy_to_string(
     libfdatetime_date_time_values_t *date_time_values,
     uint8_t *string,
     size_t string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error )
{
	libfdatetime_character_t *month_string  = NULL;
	static char *function                   = "libfdatetime_date_time_values_copy_to_string";
	int print_count                         = 0;

	if( date_time_values == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid date time values.",
		 function );

		return( -1 );
	}
	if( string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME ) == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format flags: 0x02%" PRIx8 ".",
		 function,
		 string_format_flags );

		return( -1 );
	}
	if( ( date_time_format != LIBFDATETIME_DATE_TIME_FORMAT_CTIME )
	 && ( date_time_format != LIBFDATETIME_DATE_TIME_FORMAT_ISO8601 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported date and time format: %d.",
		 function,
		 date_time_format );

		return( -1 );
	}
	/* Validate the date and time if necessary
	 */
	if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE )
	{
		if( date_time_values->year > 9999 )
		{
			return( 0 );
		}
		if( ( date_time_values->month == 0 )
		 || ( date_time_values->month >= 13 ) )
		{
			return( 0 );
		}
		/* TODO add a more sophisticate day of the month check */
		if( ( date_time_values->day == 0 )
		 || ( date_time_values->day >= 32 ) )
		{
			return( 0 );
		}
	}
	if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_TIME )
	{
		if( date_time_values->hours >= 24 )
		{
			return( 0 );
		}
		if( date_time_values->minutes >= 60 )
		{
			return( 0 );
		}
		if( date_time_values->seconds >= 60 )
		{
			return( 0 );
		}
	}
	/* Create the date and time string
	 */
	if( date_time_format == LIBFDATETIME_DATE_TIME_FORMAT_CTIME )
	{
		switch( date_time_values->month )
		{
			case 1:
				month_string = _LIBFDATETIME_STRING( "Jan" );
				break;
			case 2:
				month_string = _LIBFDATETIME_STRING( "Feb" );
				break;
			case 3:
				month_string = _LIBFDATETIME_STRING( "Mar" );
				break;
			case 4:
				month_string = _LIBFDATETIME_STRING( "Apr" );
				break;
			case 5:
				month_string = _LIBFDATETIME_STRING( "May" );
				break;
			case 6:
				month_string = _LIBFDATETIME_STRING( "Jun" );
				break;
			case 7:
				month_string = _LIBFDATETIME_STRING( "Jul" );
				break;
			case 8:
				month_string = _LIBFDATETIME_STRING( "Aug" );
				break;
			case 9:
				month_string = _LIBFDATETIME_STRING( "Sep" );
				break;
			case 10:
				month_string = _LIBFDATETIME_STRING( "Oct" );
				break;
			case 11:
				month_string = _LIBFDATETIME_STRING( "Nov" );
				break;
			case 12:
				month_string = _LIBFDATETIME_STRING( "Dec" );
				break;
		}
		if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME )
		{
			if( string_size < 22 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: string is too small.",
				 function );

				return( -1 );
			}
			print_count = libfdatetime_string_snprintf(
				       string,
				       string_size,
				       "%s %02u, %04u %02u:%02u:%02u",
				       (char *) month_string,
				       date_time_values->day,
				       date_time_values->year,
				       date_time_values->hours,
				       date_time_values->minutes,
				       date_time_values->seconds );
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE )
		{
			if( string_size < 13 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: string is too small.",
				 function );

				return( -1 );
			}
			print_count = libfdatetime_string_snprintf(
				       string,
				       string_size,
				       "%s %02u, %04u",
				       (char *) month_string,
				       date_time_values->day,
				       date_time_values->year );
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_TIME )
		{
			if( string_size < 9 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: string is too small.",
				 function );

				return( -1 );
			}
			print_count = libfdatetime_string_snprintf(
				       string,
				       string_size,
				       "%02u:%02u:%02u",
				       date_time_values->hours,
				       date_time_values->minutes,
				       date_time_values->seconds );
		}
	}
	else if( date_time_format == LIBFDATETIME_DATE_TIME_FORMAT_ISO8601 )
	{
		if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME )
		{
			if( string_size < 20 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: string is too small.",
				 function );

				return( -1 );
			}
			print_count = libfdatetime_string_snprintf(
				       string,
				       string_size,
				       "%04d-%02d-%02dT%02d:%02d:%02d",
				       date_time_values->year,
				       date_time_values->month,
				       date_time_values->day,
				       date_time_values->hours,
				       date_time_values->minutes,
				       date_time_values->seconds );
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE )
		{
			if( string_size < 11 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: string is too small.",
				 function );

				return( -1 );
			}
			print_count = libfdatetime_string_snprintf(
				       string,
				       string_size,
				       "%04d-%02d-%02d",
				       date_time_values->year,
				       date_time_values->month,
				       date_time_values->day );
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_TIME )
		{
			if( string_size < 9 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: string is too small.",
				 function );

				return( -1 );
			}
			print_count = libfdatetime_string_snprintf(
				       string,
				       string_size,
				       "%02d:%02d:%02d",
				       date_time_values->hours,
				       date_time_values->minutes,
				       date_time_values->seconds );
		}
	}
	if( ( print_count < 0 )
	 || ( (size_t) print_count > string_size ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

