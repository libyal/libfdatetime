/*
 * Date and time values functions
 *
 * Copyright (c) 2008-2010, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations.
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
#include <narrow_string.h>
#include <types.h>

#include <liberror.h>

#include "libfdatetime_definitions.h"
#include "libfdatetime_date_time_values.h"
#include "libfdatetime_string.h"
#include "libfdatetime_types.h"

/* Deterimes the size of the string for the date and time values
 * The string size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_date_time_values_get_string_size(
     libfdatetime_date_time_values_t *date_time_values,
     size_t *string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error )
{
	static char *function = "libfdatetime_date_time_values_get_string_size";

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
	if( string_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string size.",
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
	/* Create the date and time string
	 */
	if( date_time_format == LIBFDATETIME_DATE_TIME_FORMAT_CTIME )
	{
		if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME )
		{
			*string_size = 22;
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE )
		{
			*string_size = 13;
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_TIME )
		{
			*string_size = 9;
		}
	}
	else if( date_time_format == LIBFDATETIME_DATE_TIME_FORMAT_ISO8601 )
	{
		if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME )
		{
			*string_size = 20;
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE )
		{
			*string_size = 11;
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_TIME )
		{
			*string_size = 9;
		}
	}
	return( 1 );
}

/* Converts the date and time values into an UTF-8 string
 * The string size should include the end of string character
 * Returns 1 if successful, 0 if the date and time values are not a valid or -1 on error
 */
int libfdatetime_date_time_values_copy_to_utf8_string(
     libfdatetime_date_time_values_t *date_time_values,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error )
{
	char *month_string    = NULL;
	static char *function = "libfdatetime_date_time_values_copy_to_utf8_string";
	size_t string_index   = 0;
	uint16_t year_value   = 0;

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
	if( utf8_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
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
				month_string = "Jan";
				break;
			case 2:
				month_string = "Feb";
				break;
			case 3:
				month_string = "Mar";
				break;
			case 4:
				month_string = "Apr";
				break;
			case 5:
				month_string = "May";
				break;
			case 6:
				month_string = "Jun";
				break;
			case 7:
				month_string = "Jul";
				break;
			case 8:
				month_string = "Aug";
				break;
			case 9:
				month_string = "Sep";
				break;
			case 10:
				month_string = "Oct";
				break;
			case 11:
				month_string = "Nov";
				break;
			case 12:
				month_string = "Dec";
				break;
		}
		if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME )
		{
			if( utf8_string_size < 22 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-8 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: mmm dd, yyyy HH:MM:SS */
			utf8_string[ string_index++ ] = (uint8_t) month_string[ 0 ];
			utf8_string[ string_index++ ] = (uint8_t) month_string[ 1 ];
			utf8_string[ string_index++ ] = (uint8_t) month_string[ 2 ];

			utf8_string[ string_index++ ] = (uint8_t) ' ';

			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->day / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->day % 10 );

			utf8_string[ string_index++ ] = (uint8_t) ',';
			utf8_string[ string_index++ ] = (uint8_t) ' ';

			year_value                    = date_time_values->year;
			utf8_string[ string_index++ ] = (uint8_t) '0' + (uint8_t) ( year_value / 1000 );
			year_value                   %= 1000;
			utf8_string[ string_index++ ] = (uint8_t) '0' + (uint8_t) ( year_value / 100 );
			year_value                   %= 100;
			utf8_string[ string_index++ ] = (uint8_t) '0' + (uint8_t) ( year_value / 10 );
			year_value                   %= 10;
			utf8_string[ string_index++ ] = (uint8_t) '0' + (uint8_t) year_value;

			utf8_string[ string_index++ ] = (uint8_t) ' ';

			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->hours / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->hours % 10 );

			utf8_string[ string_index++ ] = (uint8_t) ':';

			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->minutes / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->minutes % 10 );

			utf8_string[ string_index++ ] = (uint8_t) ':';

			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->seconds / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->seconds % 10 );

			utf8_string[ string_index++ ] = 0;
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE )
		{
			if( utf8_string_size < 13 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-8 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: mmm dd, yyyy */
			utf8_string[ string_index++ ] = (uint8_t) month_string[ 0 ];
			utf8_string[ string_index++ ] = (uint8_t) month_string[ 1 ];
			utf8_string[ string_index++ ] = (uint8_t) month_string[ 2 ];

			utf8_string[ string_index++ ] = (uint8_t) ' ';

			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->day / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->day % 10 );

			utf8_string[ string_index++ ] = (uint8_t) ',';
			utf8_string[ string_index++ ] = (uint8_t) ' ';

			year_value                    = date_time_values->year;
			utf8_string[ string_index++ ] = (uint8_t) '0' + (uint8_t) ( year_value / 1000 );
			year_value                   %= 1000;
			utf8_string[ string_index++ ] = (uint8_t) '0' + (uint8_t) ( year_value / 100 );
			year_value                   %= 100;
			utf8_string[ string_index++ ] = (uint8_t) '0' + (uint8_t) ( year_value / 10 );
			year_value                   %= 10;
			utf8_string[ string_index++ ] = (uint8_t) '0' + (uint8_t) year_value;

			utf8_string[ string_index++ ] = 0;
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_TIME )
		{
			if( utf8_string_size < 9 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-8 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: HH:MM:SS */
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->hours / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->hours % 10 );

			utf8_string[ string_index++ ] = (uint8_t) ':';

			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->minutes / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->minutes % 10 );

			utf8_string[ string_index++ ] = (uint8_t) ':';

			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->seconds / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->seconds % 10 );

			utf8_string[ string_index++ ] = 0;
		}
	}
	else if( date_time_format == LIBFDATETIME_DATE_TIME_FORMAT_ISO8601 )
	{
		if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME )
		{
			if( utf8_string_size < 20 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-8 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: yyyy-mm-ddTHH:MM:SS */
			year_value                    = date_time_values->year;
			utf8_string[ string_index++ ] = (uint8_t) '0' + (uint8_t) ( year_value / 1000 );
			year_value                   %= 1000;
			utf8_string[ string_index++ ] = (uint8_t) '0' + (uint8_t) ( year_value / 100 );
			year_value                   %= 100;
			utf8_string[ string_index++ ] = (uint8_t) '0' + (uint8_t) ( year_value / 10 );
			year_value                   %= 10;
			utf8_string[ string_index++ ] = (uint8_t) '0' + (uint8_t) year_value;

			utf8_string[ string_index++ ] = (uint8_t) '-';

			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->month / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->month % 10 );

			utf8_string[ string_index++ ] = (uint8_t) '-';

			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->day / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->day % 10 );

			utf8_string[ string_index++ ] = (uint8_t) 'T';

			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->hours / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->hours % 10 );

			utf8_string[ string_index++ ] = (uint8_t) ':';

			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->minutes / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->minutes % 10 );

			utf8_string[ string_index++ ] = (uint8_t) ':';

			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->seconds / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->seconds % 10 );

			utf8_string[ string_index++ ] = 0;
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE )
		{
			if( utf8_string_size < 11 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-8 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: yyyy-mm-dd */
			year_value                    = date_time_values->year;
			utf8_string[ string_index++ ] = (uint8_t) '0' + (uint8_t) ( year_value / 1000 );
			year_value                   %= 1000;
			utf8_string[ string_index++ ] = (uint8_t) '0' + (uint8_t) ( year_value / 100 );
			year_value                   %= 100;
			utf8_string[ string_index++ ] = (uint8_t) '0' + (uint8_t) ( year_value / 10 );
			year_value                   %= 10;
			utf8_string[ string_index++ ] = (uint8_t) '0' + (uint8_t) year_value;

			utf8_string[ string_index++ ] = (uint8_t) '-';

			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->month / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->month % 10 );

			utf8_string[ string_index++ ] = (uint8_t) '-';

			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->day / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->day % 10 );

			utf8_string[ string_index++ ] = 0;
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_TIME )
		{
			if( utf8_string_size < 9 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-8 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: HH:MM:SS */
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->hours / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->hours % 10 );

			utf8_string[ string_index++ ] = (uint8_t) ':';

			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->minutes / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->minutes % 10 );

			utf8_string[ string_index++ ] = (uint8_t) ':';

			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->seconds / 10 );
			utf8_string[ string_index++ ] = (uint8_t) '0' + ( date_time_values->seconds % 10 );

			utf8_string[ string_index++ ] = 0;
		}
	}
	return( 1 );
}

/* Converts the date and time values into an UTF-16 string
 * The string size should include the end of string character
 * Returns 1 if successful, 0 if the date and time values are not a valid or -1 on error
 */
int libfdatetime_date_time_values_copy_to_utf16_string(
     libfdatetime_date_time_values_t *date_time_values,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error )
{
	char *month_string    = NULL;
	static char *function = "libfdatetime_date_time_values_copy_to_utf16_string";
	size_t string_index   = 0;
	uint16_t year_value   = 0;

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
	if( utf16_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
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
				month_string = "Jan";
				break;
			case 2:
				month_string = "Feb";
				break;
			case 3:
				month_string = "Mar";
				break;
			case 4:
				month_string = "Apr";
				break;
			case 5:
				month_string = "May";
				break;
			case 6:
				month_string = "Jun";
				break;
			case 7:
				month_string = "Jul";
				break;
			case 8:
				month_string = "Aug";
				break;
			case 9:
				month_string = "Sep";
				break;
			case 10:
				month_string = "Oct";
				break;
			case 11:
				month_string = "Nov";
				break;
			case 12:
				month_string = "Dec";
				break;
		}
		if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME )
		{
			if( utf16_string_size < 22 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-16 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: mmm dd, yyyy HH:MM:SS */
			utf16_string[ string_index++ ] = (uint16_t) month_string[ 0 ];
			utf16_string[ string_index++ ] = (uint16_t) month_string[ 1 ];
			utf16_string[ string_index++ ] = (uint16_t) month_string[ 2 ];

			utf16_string[ string_index++ ] = (uint16_t) ' ';

			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->day / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->day % 10 );

			utf16_string[ string_index++ ] = (uint16_t) ',';
			utf16_string[ string_index++ ] = (uint16_t) ' ';

			year_value                     = date_time_values->year;
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( year_value / 1000 );
			year_value                    %= 1000;
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( year_value / 100 );
			year_value                    %= 100;
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( year_value / 10 );
			year_value                    %= 10;
			utf16_string[ string_index++ ] = (uint16_t) '0' + year_value;

			utf16_string[ string_index++ ] = (uint16_t) ' ';

			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->hours / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->hours % 10 );

			utf16_string[ string_index++ ] = (uint16_t) ':';

			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->minutes / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->minutes % 10 );

			utf16_string[ string_index++ ] = (uint16_t) ':';

			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->seconds / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->seconds % 10 );

			utf16_string[ string_index++ ] = 0;
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE )
		{
			if( utf16_string_size < 13 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-16 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: mmm dd, yyyy */
			utf16_string[ string_index++ ] = (uint16_t) month_string[ 0 ];
			utf16_string[ string_index++ ] = (uint16_t) month_string[ 1 ];
			utf16_string[ string_index++ ] = (uint16_t) month_string[ 2 ];

			utf16_string[ string_index++ ] = (uint16_t) ' ';

			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->day / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->day % 10 );

			utf16_string[ string_index++ ] = (uint16_t) ',';
			utf16_string[ string_index++ ] = (uint16_t) ' ';

			year_value                     = date_time_values->year;
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( year_value / 1000 );
			year_value                    %= 1000;
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( year_value / 100 );
			year_value                    %= 100;
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( year_value / 10 );
			year_value                    %= 10;
			utf16_string[ string_index++ ] = (uint16_t) '0' + year_value;

			utf16_string[ string_index++ ] = 0;
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_TIME )
		{
			if( utf16_string_size < 9 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-16 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: HH:MM:SS */
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->hours / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->hours % 10 );

			utf16_string[ string_index++ ] = (uint16_t) ':';

			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->minutes / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->minutes % 10 );

			utf16_string[ string_index++ ] = (uint16_t) ':';

			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->seconds / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->seconds % 10 );

			utf16_string[ string_index++ ] = 0;
		}
	}
	else if( date_time_format == LIBFDATETIME_DATE_TIME_FORMAT_ISO8601 )
	{
		if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME )
		{
			if( utf16_string_size < 20 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-16 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: yyyy-mm-ddTHH:MM:SS */
			year_value                     = date_time_values->year;
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( year_value / 1000 );
			year_value                    %= 1000;
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( year_value / 100 );
			year_value                    %= 100;
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( year_value / 10 );
			year_value                    %= 10;
			utf16_string[ string_index++ ] = (uint16_t) '0' + year_value;

			utf16_string[ string_index++ ] = (uint16_t) '-';

			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->month / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->month % 10 );

			utf16_string[ string_index++ ] = (uint16_t) '-';

			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->day / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->day % 10 );

			utf16_string[ string_index++ ] = (uint16_t) 'T';

			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->hours / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->hours % 10 );

			utf16_string[ string_index++ ] = (uint16_t) ':';

			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->minutes / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->minutes % 10 );

			utf16_string[ string_index++ ] = (uint16_t) ':';

			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->seconds / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->seconds % 10 );

			utf16_string[ string_index++ ] = 0;
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE )
		{
			if( utf16_string_size < 11 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-16 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: yyyy-mm-dd */
			year_value                     = date_time_values->year;
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( year_value / 1000 );
			year_value                    %= 1000;
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( year_value / 100 );
			year_value                    %= 100;
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( year_value / 10 );
			year_value                    %= 10;
			utf16_string[ string_index++ ] = (uint16_t) '0' + year_value;

			utf16_string[ string_index++ ] = (uint16_t) '-';

			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->month / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->month % 10 );

			utf16_string[ string_index++ ] = (uint16_t) '-';

			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->day / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->day % 10 );

			utf16_string[ string_index++ ] = 0;
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_TIME )
		{
			if( utf16_string_size < 9 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-16 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: HH:MM:SS */
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->hours / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->hours % 10 );

			utf16_string[ string_index++ ] = (uint16_t) ':';

			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->minutes / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->minutes % 10 );

			utf16_string[ string_index++ ] = (uint16_t) ':';

			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->seconds / 10 );
			utf16_string[ string_index++ ] = (uint16_t) '0' + ( date_time_values->seconds % 10 );

			utf16_string[ string_index++ ] = 0;
		}
	}
	return( 1 );
}

/* Converts the date and time values into an UTF-32 string
 * The string size should include the end of string character
 * Returns 1 if successful, 0 if the date and time values are not a valid or -1 on error
 */
int libfdatetime_date_time_values_copy_to_utf32_string(
     libfdatetime_date_time_values_t *date_time_values,
     uint32_t *utf32_string,
     size_t utf32_string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error )
{
	char *month_string    = NULL;
	static char *function = "libfdatetime_date_time_values_copy_to_utf32_string";
	size_t string_index   = 0;
	uint16_t year_value   = 0;

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
	if( utf32_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string.",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.",
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
				month_string = "Jan";
				break;
			case 2:
				month_string = "Feb";
				break;
			case 3:
				month_string = "Mar";
				break;
			case 4:
				month_string = "Apr";
				break;
			case 5:
				month_string = "May";
				break;
			case 6:
				month_string = "Jun";
				break;
			case 7:
				month_string = "Jul";
				break;
			case 8:
				month_string = "Aug";
				break;
			case 9:
				month_string = "Sep";
				break;
			case 10:
				month_string = "Oct";
				break;
			case 11:
				month_string = "Nov";
				break;
			case 12:
				month_string = "Dec";
				break;
		}
		if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME )
		{
			if( utf32_string_size < 22 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-32 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: mmm dd, yyyy HH:MM:SS */
			utf32_string[ string_index++ ] = (uint32_t) month_string[ 0 ];
			utf32_string[ string_index++ ] = (uint32_t) month_string[ 1 ];
			utf32_string[ string_index++ ] = (uint32_t) month_string[ 2 ];

			utf32_string[ string_index++ ] = (uint32_t) ' ';

			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->day / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->day % 10 );

			utf32_string[ string_index++ ] = (uint32_t) ',';
			utf32_string[ string_index++ ] = (uint32_t) ' ';

			year_value                     = date_time_values->year;
			utf32_string[ string_index++ ] = (uint32_t) '0' + (uint32_t) ( year_value / 1000 );
			year_value                    %= 1000;
			utf32_string[ string_index++ ] = (uint32_t) '0' + (uint32_t) ( year_value / 100 );
			year_value                    %= 100;
			utf32_string[ string_index++ ] = (uint32_t) '0' + (uint32_t) ( year_value / 10 );
			year_value                    %= 10;
			utf32_string[ string_index++ ] = (uint32_t) '0' + (uint32_t) year_value;

			utf32_string[ string_index++ ] = (uint32_t) ' ';

			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->hours / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->hours % 10 );

			utf32_string[ string_index++ ] = (uint32_t) ':';

			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->minutes / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->minutes % 10 );

			utf32_string[ string_index++ ] = (uint32_t) ':';

			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->seconds / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->seconds % 10 );

			utf32_string[ string_index++ ] = 0;
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE )
		{
			if( utf32_string_size < 13 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-32 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: mmm dd, yyyy */
			utf32_string[ string_index++ ] = (uint32_t) month_string[ 0 ];
			utf32_string[ string_index++ ] = (uint32_t) month_string[ 1 ];
			utf32_string[ string_index++ ] = (uint32_t) month_string[ 2 ];

			utf32_string[ string_index++ ] = (uint32_t) ' ';

			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->day / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->day % 10 );

			utf32_string[ string_index++ ] = (uint32_t) ',';
			utf32_string[ string_index++ ] = (uint32_t) ' ';

			year_value                     = date_time_values->year;
			utf32_string[ string_index++ ] = (uint32_t) '0' + (uint32_t) ( year_value / 1000 );
			year_value                    %= 1000;
			utf32_string[ string_index++ ] = (uint32_t) '0' + (uint32_t) ( year_value / 100 );
			year_value                    %= 100;
			utf32_string[ string_index++ ] = (uint32_t) '0' + (uint32_t) ( year_value / 10 );
			year_value                    %= 10;
			utf32_string[ string_index++ ] = (uint32_t) '0' + (uint32_t) year_value;

			utf32_string[ string_index++ ] = 0;
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_TIME )
		{
			if( utf32_string_size < 9 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-32 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: HH:MM:SS */
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->hours / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->hours % 10 );

			utf32_string[ string_index++ ] = (uint32_t) ':';

			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->minutes / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->minutes % 10 );

			utf32_string[ string_index++ ] = (uint32_t) ':';

			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->seconds / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->seconds % 10 );

			utf32_string[ string_index++ ] = 0;
		}
	}
	else if( date_time_format == LIBFDATETIME_DATE_TIME_FORMAT_ISO8601 )
	{
		if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME )
		{
			if( utf32_string_size < 20 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-32 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: yyyy-mm-ddTHH:MM:SS */
			year_value                     = date_time_values->year;
			utf32_string[ string_index++ ] = (uint32_t) '0' + (uint32_t) ( year_value / 1000 );
			year_value                    %= 1000;
			utf32_string[ string_index++ ] = (uint32_t) '0' + (uint32_t) ( year_value / 100 );
			year_value                    %= 100;
			utf32_string[ string_index++ ] = (uint32_t) '0' + (uint32_t) ( year_value / 10 );
			year_value                    %= 10;
			utf32_string[ string_index++ ] = (uint32_t) '0' + (uint32_t) year_value;

			utf32_string[ string_index++ ] = (uint32_t) '-';

			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->month / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->month % 10 );

			utf32_string[ string_index++ ] = (uint32_t) '-';

			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->day / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->day % 10 );

			utf32_string[ string_index++ ] = (uint32_t) 'T';

			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->hours / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->hours % 10 );

			utf32_string[ string_index++ ] = (uint32_t) ':';

			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->minutes / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->minutes % 10 );

			utf32_string[ string_index++ ] = (uint32_t) ':';

			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->seconds / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->seconds % 10 );

			utf32_string[ string_index++ ] = 0;
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_DATE ) == LIBFDATETIME_STRING_FORMAT_FLAG_DATE )
		{
			if( utf32_string_size < 11 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-32 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: yyyy-mm-dd */
			year_value                     = date_time_values->year;
			utf32_string[ string_index++ ] = (uint32_t) '0' + (uint32_t) ( year_value / 1000 );
			year_value                    %= 1000;
			utf32_string[ string_index++ ] = (uint32_t) '0' + (uint32_t) ( year_value / 100 );
			year_value                    %= 100;
			utf32_string[ string_index++ ] = (uint32_t) '0' + (uint32_t) ( year_value / 10 );
			year_value                    %= 10;
			utf32_string[ string_index++ ] = (uint32_t) '0' + (uint32_t) year_value;

			utf32_string[ string_index++ ] = (uint32_t) '-';

			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->month / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->month % 10 );

			utf32_string[ string_index++ ] = (uint32_t) '-';

			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->day / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->day % 10 );

			utf32_string[ string_index++ ] = 0;
		}
		else if( ( string_format_flags & LIBFDATETIME_STRING_FORMAT_FLAG_TIME ) == LIBFDATETIME_STRING_FORMAT_FLAG_TIME )
		{
			if( utf32_string_size < 9 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-32 string is too small.",
				 function );

				return( -1 );
			}
			/* Format: HH:MM:SS */
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->hours / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->hours % 10 );

			utf32_string[ string_index++ ] = (uint32_t) ':';

			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->minutes / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->minutes % 10 );

			utf32_string[ string_index++ ] = (uint32_t) ':';

			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->seconds / 10 );
			utf32_string[ string_index++ ] = (uint32_t) '0' + ( date_time_values->seconds % 10 );

			utf32_string[ string_index++ ] = 0;
		}
	}
	return( 1 );
}

