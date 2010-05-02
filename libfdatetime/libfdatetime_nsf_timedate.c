/*
 * Notes Storage Facility (NSF) timedate functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include <liberror.h>

#include "libfdatetime_definitions.h"
#include "libfdatetime_date_time_values.h"
#include "libfdatetime_nsf_timedate.h"
#include "libfdatetime_types.h"

/* Initialize an nsf timedate
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_nsf_timedate_initialize(
     libfdatetime_nsf_timedate_t **nsf_timedate,
     liberror_error_t **error )
{
	libfdatetime_internal_nsf_timedate_t *internal_nsf_timedate = NULL;
	static char *function                                       = "libfdatetime_nsf_timedate_initialize";

	if( nsf_timedate == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid nsf_timedate.",
		 function );

		return( -1 );
	}
	if( *nsf_timedate == NULL )
	{
		internal_nsf_timedate = (libfdatetime_internal_nsf_timedate_t *) memory_allocate(
		                                                                  sizeof( libfdatetime_internal_nsf_timedate_t ) );

		if( internal_nsf_timedate == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create nsf_timedate.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     internal_nsf_timedate,
		     0,
		     sizeof( libfdatetime_internal_nsf_timedate_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear nsf_timedate.",
			 function );

			memory_free(
			 internal_nsf_timedate );

			return( -1 );
		}
		*nsf_timedate = (libfdatetime_nsf_timedate_t *) internal_nsf_timedate;
	}
	return( 1 );
}

/* Frees an exisisting nsf_timedate
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_nsf_timedate_free(
     libfdatetime_nsf_timedate_t **nsf_timedate,
     liberror_error_t **error )
{
	libfdatetime_internal_nsf_timedate_t *internal_nsf_timedate = NULL;
	static char *function                                       = "libfdatetime_nsf_timedate_free";

	if( nsf_timedate == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid nsf_timedate.",
		 function );

		return( -1 );
	}
	if( *nsf_timedate != NULL )
	{
		internal_nsf_timedate = (libfdatetime_internal_nsf_timedate_t *) *nsf_timedate;

		memory_free(
		 internal_nsf_timedate );

		*nsf_timedate = NULL;
	}
	return( 1 );
}

/* Converts a byte stream into an nsf timedate
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_nsf_timedate_copy_from_byte_stream(
     libfdatetime_nsf_timedate_t *nsf_timedate,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     uint8_t byte_order,
     liberror_error_t **error )
{
	libfdatetime_internal_nsf_timedate_t *internal_nsf_timedate = NULL;
	static char *function                                       = "libfdatetime_nsf_timedate_copy_from_byte_stream";

	if( nsf_timedate == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid nsf_timedate.",
		 function );

		return( -1 );
	}
	internal_nsf_timedate = (libfdatetime_internal_nsf_timedate_t *) nsf_timedate;

	if( byte_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size < 8 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream too small.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: byte stream size exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBFDATETIME_ENDIAN_BIG )
	 && ( byte_order != LIBFDATETIME_ENDIAN_LITTLE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	if( byte_order == LIBFDATETIME_ENDIAN_LITTLE )
	{
		byte_stream_copy_to_uint32_little_endian(
		 byte_stream,
		 internal_nsf_timedate->lower );

		byte_stream += 4;

		byte_stream_copy_to_uint32_little_endian(
		byte_stream,
		internal_nsf_timedate->upper );
	}
	else if( byte_order == LIBFDATETIME_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint32_big_endian(
		 byte_stream,
		 internal_nsf_timedate->upper );

		byte_stream += 4;

		byte_stream_copy_to_uint32_big_endian(
		byte_stream,
		internal_nsf_timedate->lower );
	}
	return( 1 );
}

/* Converts a 64-bit value into an nsf timedate
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_nsf_timedate_copy_from_uint64(
     libfdatetime_nsf_timedate_t *nsf_timedate,
     uint64_t value_64bit,
     liberror_error_t **error )
{
	libfdatetime_internal_nsf_timedate_t *internal_nsf_timedate = NULL;
	static char *function                                       = "libfdatetime_nsf_timedate_copy_from_uint64";

	if( nsf_timedate == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid nsf_timedate.",
		 function );

		return( -1 );
	}
	internal_nsf_timedate = (libfdatetime_internal_nsf_timedate_t *) nsf_timedate;

	internal_nsf_timedate->upper = value_64bit >> 32;
	internal_nsf_timedate->lower = value_64bit & 0x0ffffffffULL;

	return( 1 );
}

/* Converts an nsf timedate into date time values
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_nsf_timedate_copy_to_date_time_values(
     libfdatetime_internal_nsf_timedate_t *internal_nsf_timedate,
     libfdatetime_date_time_values_t *date_time_values,
     liberror_error_t **error )
{
	static char *function          = "libfdatetime_nsf_timedate_copy_to_date_time_values";
	uint32_t nsf_julian_day        = 0;
	uint32_t nsf_time              = 0;
	uint32_t number_of_years       = 0;
	uint32_t number_of_months      = 0;
	uint32_t julian_quad_cycles    = 0;
	uint32_t gregorian_cent_cycles = 0;
	uint32_t gregorian_quad_cycles = 0;
	uint32_t roman_annual_cycles   = 0;

	if( internal_nsf_timedate == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal nsf_timedate.",
		 function );

		return( -1 );
	}
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
	/* TODO what about dates before 1582 ? */

	/* Retrieve the Julian day value which is stored in the 24 LSB of the upper value
	 * the NSF Julian day starts with January 1, 4713 BC 00:00 UTC
	 * instead of January 1, 4713 BC 12:00 UTC
	 */
	nsf_julian_day = internal_nsf_timedate->upper & 0x00ffffffUL;

	/* Shift the epoch back to March 1, 4800 BC 00:00
	 * This is the beginning of the Gregorian quadricentennial
	 * which is 32044 days before the Julian period
	 */
	nsf_julian_day += 32044;

	/* Determine the number of Gregorian quadricentennial cycles
	 * 1 cycle consists of 146097 days
	 */
	gregorian_quad_cycles = nsf_julian_day / 146097;

	nsf_julian_day %= 146097;

	/* Determine the number of Gregorian centennial cycles
	 * 1 cycle consists of 36524 days
	 * Correct for leap years per cycle, either 3 or 4
	 */
	gregorian_cent_cycles = ( ( ( nsf_julian_day / 36524 ) + 1 ) * 3 ) / 4;

	nsf_julian_day -= gregorian_cent_cycles * 36524;

	/* Determine the number of Julian quadrennial cycles
	 * 1 cycle consists of 1461 days per 4 year
	 */
	julian_quad_cycles = nsf_julian_day / 1461;

	nsf_julian_day %= 1461;

	/* Determine the number of Roman annual cycles
	 * 1 cycle consists of 365 days
	 * Correct for leap years per cycle, either 3 or 4
	 */
	roman_annual_cycles = ( ( ( nsf_julian_day / 365 ) + 1 ) * 3 ) / 4;

	/* The number of days remaining in the current Julian year
	 */
	nsf_julian_day -= roman_annual_cycles * 365;

	/* Determine the number of years since March 1, 4801 BC
	 */
	number_of_years = ( gregorian_quad_cycles * 400 )
	                + ( gregorian_cent_cycles * 100 )
	                + ( julian_quad_cycles * 4 )
	                + roman_annual_cycles;

	/* Determine the number of months since March
	 */
	number_of_months = ( ( ( nsf_julian_day * 5 ) + 308 ) / 153 ) - 2;

	/* Determine the number of days since the 1st of the month
	 */
	nsf_julian_day -= ( ( ( number_of_months + 4 ) * 153 ) / 5 );
	nsf_julian_day += 122;

	/* Determine the year
	 */
	date_time_values->year = (uint16_t) ( number_of_years - 4800 + ( ( number_of_months + 2 ) / 12 ) );

	/* Determine the month
	 */
	date_time_values->month = ( ( number_of_months + 2 ) % 12 ) + 1;

	/* Determine the day of the month
	 */
	date_time_values->day = (uint8_t) ( nsf_julian_day + 1 );

	/* Retrieve the number of seconds from the lower part of the NFS timedate
	 * which contains the number of 100th of seconds
	 */ 
	nsf_time = internal_nsf_timedate->lower / 100;

	/* There are 60 seconds in a minute correct the value to minutes
	 */
	date_time_values->seconds = nsf_time % 60;
	nsf_time                 /= 60;

	/* There are 60 minutes in an hour correct the value to hours
	 */
	date_time_values->minutes = nsf_time % 60;
	nsf_time                 /= 60;

	/* There are 24 hours in a day correct the value to days
	 */
	date_time_values->hours = (uint8_t) nsf_time;

	/* TODO day light savings and timezone */

	return( 1 );
}

/* Deterimes the size of the string for the nsf_timedate
 * The string size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_nsf_timedate_get_string_size(
     libfdatetime_nsf_timedate_t *nsf_timedate,
     size_t *string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error )
{
	libfdatetime_date_time_values_t date_time_values;

	static char *function = "libfdatetime_nsf_timedate_get_string_size";

	if( nsf_timedate == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid nsf_timedate.",
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
	if( libfdatetime_nsf_timedate_copy_to_date_time_values(
	     (libfdatetime_internal_nsf_timedate_t *) nsf_timedate,
	     &date_time_values,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set date time values.",
		 function );

		return( -1 );
	}
	/* Create the date and time string
	 */
	if( libfdatetime_date_time_values_get_string_size(
	     &date_time_values,
	     string_size,
	     string_format_flags,
	     date_time_format,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to get string size.",
		 function );

		return( -1 );
	}
	/* Make sure the string can hold the hexadecimal representation
	 * of an nsf timedate
	 */
	if( *string_size < 24 )
	{
		*string_size = 24;
	}
	return( 1 );
}

/* Converts the nsf_timedate into an UTF-8 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_nsf_timedate_copy_to_utf8_string(
     libfdatetime_nsf_timedate_t *nsf_timedate,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error )
{
	libfdatetime_date_time_values_t date_time_values;

	libfdatetime_internal_nsf_timedate_t *internal_nsf_timedate = NULL;
	static char *function                                       = "libfdatetime_nsf_timedate_copy_to_utf8_string";
	size_t string_index                                         = 0;
	uint8_t byte_value                                          = 0;
	uint8_t byte_shift                                          = 0;
	int result                                                  = 0;

	if( nsf_timedate == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid nsf_timedate.",
		 function );

		return( -1 );
	}
	internal_nsf_timedate = (libfdatetime_internal_nsf_timedate_t *) nsf_timedate;

	if( libfdatetime_nsf_timedate_copy_to_date_time_values(
	     internal_nsf_timedate,
	     &date_time_values,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set date time values.",
		 function );

		return( -1 );
	}
	/* Create the date and time string
	 */
	result = libfdatetime_date_time_values_copy_to_utf8_string(
	          &date_time_values,
	          utf8_string,
	          utf8_string_size,
	          string_format_flags,
	          date_time_format,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set string.",
		 function );

		return( -1 );
	}
	else if( result == 0 )
	{
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
		if( utf8_string_size < 24 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-8 string is too small.",
			 function );

			return( -1 );
		}
		utf8_string[ string_index++ ] = (uint8_t) '(';
		utf8_string[ string_index++ ] = (uint8_t) '0';
		utf8_string[ string_index++ ] = (uint8_t) 'x';

		byte_shift = 28;

		do
		{
			byte_value = ( internal_nsf_timedate->upper >> byte_shift ) & 0x0f;

			if( byte_value <= 9 )
			{
				utf8_string[ string_index++ ] = (uint8_t) '0' + byte_value;
			}
			else
			{
				utf8_string[ string_index++ ] = (uint8_t) 'a' + byte_value - 10;
			}
			byte_shift -= 4;
		}
		while( byte_shift > 0 );

		utf8_string[ string_index++ ] = (uint8_t) ' ';
		utf8_string[ string_index++ ] = (uint8_t) '0';
		utf8_string[ string_index++ ] = (uint8_t) 'x';

		byte_shift = 28;

		do
		{
			byte_value = ( internal_nsf_timedate->lower >> byte_shift ) & 0x0f;

			if( byte_value <= 9 )
			{
				utf8_string[ string_index++ ] = (uint8_t) '0' + byte_value;
			}
			else
			{
				utf8_string[ string_index++ ] = (uint8_t) 'a' + byte_value - 10;
			}
			byte_shift -= 4;
		}
		while( byte_shift > 0 );

		utf8_string[ string_index++ ] = (uint8_t) ')';

		utf8_string[ string_index++ ] = 0;
	}
	return( 1 );
}

/* Converts the nsf_timedate into an UTF-16 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_nsf_timedate_copy_to_utf16_string(
     libfdatetime_nsf_timedate_t *nsf_timedate,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error )
{
	libfdatetime_date_time_values_t date_time_values;

	libfdatetime_internal_nsf_timedate_t *internal_nsf_timedate = NULL;
	static char *function                                       = "libfdatetime_nsf_timedate_copy_to_utf16_string";
	size_t string_index                                         = 0;
	uint8_t byte_value                                          = 0;
	uint8_t byte_shift                                          = 0;
	int result                                                  = 0;

	if( nsf_timedate == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid nsf_timedate.",
		 function );

		return( -1 );
	}
	internal_nsf_timedate = (libfdatetime_internal_nsf_timedate_t *) nsf_timedate;

	if( libfdatetime_nsf_timedate_copy_to_date_time_values(
	     internal_nsf_timedate,
	     &date_time_values,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set date time values.",
		 function );

		return( -1 );
	}
	/* Create the date and time string
	 */
	result = libfdatetime_date_time_values_copy_to_utf16_string(
	          &date_time_values,
	          utf16_string,
	          utf16_string_size,
	          string_format_flags,
	          date_time_format,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set string.",
		 function );

		return( -1 );
	}
	else if( result == 0 )
	{
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
		if( utf16_string_size < 24 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string is too small.",
			 function );

			return( -1 );
		}
		utf16_string[ string_index++ ] = (uint16_t) '(';
		utf16_string[ string_index++ ] = (uint16_t) '0';
		utf16_string[ string_index++ ] = (uint16_t) 'x';

		byte_shift = 28;

		do
		{
			byte_value = ( internal_nsf_timedate->upper >> byte_shift ) & 0x0f;

			if( byte_value <= 9 )
			{
				utf16_string[ string_index++ ] = (uint16_t) '0' + byte_value;
			}
			else
			{
				utf16_string[ string_index++ ] = (uint16_t) 'a' + byte_value - 10;
			}
			byte_shift -= 4;
		}
		while( byte_shift > 0 );

		utf16_string[ string_index++ ] = (uint16_t) ' ';
		utf16_string[ string_index++ ] = (uint16_t) '0';
		utf16_string[ string_index++ ] = (uint16_t) 'x';

		byte_shift = 28;

		do
		{
			byte_value = ( internal_nsf_timedate->lower >> byte_shift ) & 0x0f;

			if( byte_value <= 9 )
			{
				utf16_string[ string_index++ ] = (uint16_t) '0' + byte_value;
			}
			else
			{
				utf16_string[ string_index++ ] = (uint16_t) 'a' + byte_value - 10;
			}
			byte_shift -= 4;
		}
		while( byte_shift > 0 );

		utf16_string[ string_index++ ] = (uint16_t) ')';

		utf16_string[ string_index++ ] = 0;
	}
	return( 1 );
}

/* Converts the nsf_timedate into an UTF-32 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_nsf_timedate_copy_to_utf32_string(
     libfdatetime_nsf_timedate_t *nsf_timedate,
     uint32_t *utf32_string,
     size_t utf32_string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error )
{
	libfdatetime_date_time_values_t date_time_values;

	libfdatetime_internal_nsf_timedate_t *internal_nsf_timedate = NULL;
	static char *function                                       = "libfdatetime_nsf_timedate_copy_to_utf32_string";
	size_t string_index                                         = 0;
	uint8_t byte_value                                          = 0;
	uint8_t byte_shift                                          = 0;
	int result                                                  = 0;

	if( nsf_timedate == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid nsf_timedate.",
		 function );

		return( -1 );
	}
	internal_nsf_timedate = (libfdatetime_internal_nsf_timedate_t *) nsf_timedate;

	if( libfdatetime_nsf_timedate_copy_to_date_time_values(
	     internal_nsf_timedate,
	     &date_time_values,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set date time values.",
		 function );

		return( -1 );
	}
	/* Create the date and time string
	 */
	result = libfdatetime_date_time_values_copy_to_utf32_string(
	          &date_time_values,
	          utf32_string,
	          utf32_string_size,
	          string_format_flags,
	          date_time_format,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set string.",
		 function );

		return( -1 );
	}
	else if( result == 0 )
	{
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
		if( utf32_string_size < 24 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-32 string is too small.",
			 function );

			return( -1 );
		}
		utf32_string[ string_index++ ] = (uint32_t) '(';
		utf32_string[ string_index++ ] = (uint32_t) '0';
		utf32_string[ string_index++ ] = (uint32_t) 'x';

		byte_shift = 28;

		do
		{
			byte_value = ( internal_nsf_timedate->upper >> byte_shift ) & 0x0f;

			if( byte_value <= 9 )
			{
				utf32_string[ string_index++ ] = (uint32_t) '0' + byte_value;
			}
			else
			{
				utf32_string[ string_index++ ] = (uint32_t) 'a' + byte_value - 10;
			}
			byte_shift -= 4;
		}
		while( byte_shift > 0 );

		utf32_string[ string_index++ ] = (uint32_t) ' ';
		utf32_string[ string_index++ ] = (uint32_t) '0';
		utf32_string[ string_index++ ] = (uint32_t) 'x';

		byte_shift = 28;

		do
		{
			byte_value = ( internal_nsf_timedate->lower >> byte_shift ) & 0x0f;

			if( byte_value <= 9 )
			{
				utf32_string[ string_index++ ] = (uint32_t) '0' + byte_value;
			}
			else
			{
				utf32_string[ string_index++ ] = (uint32_t) 'a' + byte_value - 10;
			}
			byte_shift -= 4;
		}
		while( byte_shift > 0 );

		utf32_string[ string_index++ ] = (uint32_t) ')';

		utf32_string[ string_index++ ] = 0;
	}
	return( 1 );
}

