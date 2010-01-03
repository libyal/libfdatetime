/*
 * FAT date and time functions
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
#include "libfdatetime_fat_date_time.h"
#include "libfdatetime_string.h"
#include "libfdatetime_types.h"

/* Initialize a FAT date and time
 * Make sure the value file is pointing to is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_fat_date_time_initialize(
     libfdatetime_fat_date_time_t **fat_date_time,
     liberror_error_t **error )
{
	libfdatetime_internal_fat_date_time_t *internal_fat_date_time = NULL;
	static char *function                                         = "libfdatetime_fat_date_time_initialize";

	if( fat_date_time == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid FAT date time.",
		 function );

		return( -1 );
	}
	if( *fat_date_time == NULL )
	{
		internal_fat_date_time = (libfdatetime_internal_fat_date_time_t *) memory_allocate(
		                                                                   sizeof( libfdatetime_internal_fat_date_time_t ) );

		if( internal_fat_date_time == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create FAT date time.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     internal_fat_date_time,
		     0,
		     sizeof( libfdatetime_internal_fat_date_time_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear FAT date time.",
			 function );

			memory_free(
			 internal_fat_date_time );

			return( -1 );
		}
		*fat_date_time = (libfdatetime_fat_date_time_t *) internal_fat_date_time;
	}
	return( 1 );
}

/* Frees an exisisting FAT date and time
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_fat_date_time_free(
     libfdatetime_fat_date_time_t **fat_date_time,
     liberror_error_t **error )
{
	libfdatetime_internal_fat_date_time_t *internal_fat_date_time = NULL;
	static char *function                                         = "libfdatetime_fat_date_time_free";

	if( fat_date_time == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid FAT date time.",
		 function );

		return( -1 );
	}
	if( *fat_date_time != NULL )
	{
		internal_fat_date_time = (libfdatetime_internal_fat_date_time_t *) *fat_date_time;

		memory_free(
		 internal_fat_date_time );

		*fat_date_time = NULL;
	}
	return( 1 );
}

/* Converts a byte stream into a FAT date and time
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_fat_date_time_copy_from_byte_stream(
     libfdatetime_fat_date_time_t *fat_date_time,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     uint8_t byte_order,
     liberror_error_t **error )
{
	libfdatetime_internal_fat_date_time_t *internal_fat_date_time = NULL;
	static char *function                                         = "libfdatetime_fat_date_time_copy_from_byte_stream";

	if( fat_date_time == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid FAT date time.",
		 function );

		return( -1 );
	}
	internal_fat_date_time = (libfdatetime_internal_fat_date_time_t *) fat_date_time;

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
	if( byte_stream_size < 4 )
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
		byte_stream_copy_to_uint16_little_endian(
		 byte_stream,
		 internal_fat_date_time->date );

		byte_stream += 2;

		byte_stream_copy_to_uint16_little_endian(
		byte_stream,
		internal_fat_date_time->time );
	}
	else if( byte_order == LIBFDATETIME_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint16_big_endian(
		 byte_stream,
		 internal_fat_date_time->date );

		byte_stream += 2;

		byte_stream_copy_to_uint16_big_endian(
		byte_stream,
		internal_fat_date_time->time );
	}
	return( 1 );
}

/* Converts a 32-bit value into a FAT date and time
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_fat_date_time_copy_from_uint32(
     libfdatetime_fat_date_time_t *fat_date_time,
     uint32_t value_32bit,
     liberror_error_t **error )
{
	libfdatetime_internal_fat_date_time_t *internal_fat_date_time = NULL;
	static char *function                                         = "libfdatetime_fat_date_time_copy_from_uint32";

	if( fat_date_time == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid FAT date time.",
		 function );

		return( -1 );
	}
	internal_fat_date_time = (libfdatetime_internal_fat_date_time_t *) fat_date_time;

	internal_fat_date_time->time = value_32bit & 0x0ffffL;
	internal_fat_date_time->date = value_32bit >> 16;

	return( 1 );
}

/* Converts a FAT date and time into date time values
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_fat_date_time_copy_to_date_time_values(
     libfdatetime_internal_fat_date_time_t *internal_fat_date_time,
     libfdatetime_date_time_values_t *date_time_values,
     liberror_error_t **error )
{
	static char *function = "libfdatetime_fat_date_time_copy_to_date_time_values";

	if( internal_fat_date_time == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal fat date time.",
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
	/* The year value is stored in bits 9 - 15 of the date (7 bits)
	 * A year value of 0 represents 1980
	 */
	date_time_values->year = (uint16_t) ( 1980 + ( ( internal_fat_date_time->date >> 9 ) & 0x7f ) );

	/* The month value is stored in bits 5 - 8 of the date (4 bits)
	 * A month value of 1 represents January
	 */
	date_time_values->month = (uint8_t) ( ( internal_fat_date_time->date >> 5 ) & 0x0f );

	/* The day value is stored in bits 0 - 4 of the date (5 bits)
	 */
	date_time_values->day = (uint8_t) ( internal_fat_date_time->date & 0x1f );

	/* The hours value is stored in bits 11 - 15 of the time (5 bits)
	 */
	date_time_values->hours = (uint8_t) ( ( internal_fat_date_time->time >> 11 ) & 0x1f );

	/* The minutes value is stored in bits 5 - 10 of the time (6 bits)
	 */
	date_time_values->minutes = (uint8_t) ( ( internal_fat_date_time->time >> 5 ) & 0x3f );

	/* The seconds value is stored in bits 0 - 4 of the time (5 bits)
	 * The seconds are stored as 2 second intervals
	 */
	date_time_values->seconds = (uint8_t) ( internal_fat_date_time->time & 0x1f ) * 2;

	return( 1 );
}

/* Deterimes the size of the string for the fat date time
 * The string size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_fat_date_time_get_string_size(
     libfdatetime_fat_date_time_t *fat_date_time,
     size_t *string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error )
{
	libfdatetime_date_time_values_t date_time_values;

	static char *function = "libfdatetime_fat_date_time_get_string_size";

	if( fat_date_time == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid fat date time.",
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
	if( libfdatetime_fat_date_time_copy_to_date_time_values(
	     (libfdatetime_internal_fat_date_time_t *) fat_date_time,
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
	 * of a fat date time
	 */
	if( *string_size < 18 )
	{
		*string_size = 18;
	}
	return( 1 );
}

/* Converts the FAT date and time into an UTF-8 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_fat_date_time_copy_to_utf8_string(
     libfdatetime_fat_date_time_t *fat_date_time,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error )
{
	libfdatetime_date_time_values_t date_time_values;

	libfdatetime_internal_fat_date_time_t *internal_fat_date_time = NULL;
	static char *function                                         = "libfdatetime_fat_date_time_copy_to_utf8_string";
	size_t string_index                                           = 0;
	uint8_t byte_value                                            = 0;
	uint8_t byte_shift                                            = 0;
	int result                                                    = 0;

	if( fat_date_time == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid FAT date time.",
		 function );

		return( -1 );
	}
	internal_fat_date_time = (libfdatetime_internal_fat_date_time_t *) fat_date_time;

	if( libfdatetime_fat_date_time_copy_to_date_time_values(
	     internal_fat_date_time,
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
		 "%s: unable to set UTF-8 string.",
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
		if( utf8_string_size < 16 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: string is too small.",
			 function );

			return( -1 );
		}
		utf8_string[ string_index++ ] = (uint8_t) '(';
		utf8_string[ string_index++ ] = (uint8_t) '0';
		utf8_string[ string_index++ ] = (uint8_t) 'x';

		byte_shift = 12;

		do
		{
			byte_value = ( internal_fat_date_time->date >> byte_shift ) & 0x0f;

			if( byte_value <= 9 )
			{
				utf8_string[ string_index++ ] = (uint8_t) '0' + byte_value;
			}
			else
			{
				utf8_string[ string_index++ ] = (uint8_t) 'a' + byte_value;
			}
			byte_shift -= 4;
		}
		while( byte_shift > 0 );

		utf8_string[ string_index++ ] = (uint8_t) ' ';
		utf8_string[ string_index++ ] = (uint8_t) '0';
		utf8_string[ string_index++ ] = (uint8_t) 'x';

		byte_shift = 12;

		do
		{
			byte_value = ( internal_fat_date_time->time >> byte_shift ) & 0x0f;

			if( byte_value <= 9 )
			{
				utf8_string[ string_index++ ] = (uint8_t) '0' + byte_value;
			}
			else
			{
				utf8_string[ string_index++ ] = (uint8_t) 'a' + byte_value;
			}
			byte_shift -= 4;
		}
		while( byte_shift > 0 );

		utf8_string[ string_index++ ] = (uint8_t) ')';

		utf8_string[ string_index++ ] = 0;
	}
	return( 1 );
}

/* Converts the FAT date and time into an UTF-16 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_fat_date_time_copy_to_utf16_string(
     libfdatetime_fat_date_time_t *fat_date_time,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error )
{
	libfdatetime_date_time_values_t date_time_values;

	libfdatetime_internal_fat_date_time_t *internal_fat_date_time = NULL;
	static char *function                                         = "libfdatetime_fat_date_time_copy_to_utf16_string";
	size_t string_index                                           = 0;
	uint8_t byte_value                                            = 0;
	uint8_t byte_shift                                            = 0;
	int result                                                    = 0;

	if( fat_date_time == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid FAT date time.",
		 function );

		return( -1 );
	}
	internal_fat_date_time = (libfdatetime_internal_fat_date_time_t *) fat_date_time;

	if( libfdatetime_fat_date_time_copy_to_date_time_values(
	     internal_fat_date_time,
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
		 "%s: unable to set UTF-16 string.",
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
		if( utf16_string_size < 16 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: string is too small.",
			 function );

			return( -1 );
		}
		utf16_string[ string_index++ ] = (uint16_t) '(';
		utf16_string[ string_index++ ] = (uint16_t) '0';
		utf16_string[ string_index++ ] = (uint16_t) 'x';

		byte_shift = 12;

		do
		{
			byte_value = ( internal_fat_date_time->date >> byte_shift ) & 0x0f;

			if( byte_value <= 9 )
			{
				utf16_string[ string_index++ ] = (uint16_t) '0' + byte_value;
			}
			else
			{
				utf16_string[ string_index++ ] = (uint16_t) 'a' + byte_value;
			}
			byte_shift -= 4;
		}
		while( byte_shift > 0 );

		utf16_string[ string_index++ ] = (uint16_t) ' ';
		utf16_string[ string_index++ ] = (uint16_t) '0';
		utf16_string[ string_index++ ] = (uint16_t) 'x';

		byte_shift = 12;

		do
		{
			byte_value = ( internal_fat_date_time->time >> byte_shift ) & 0x0f;

			if( byte_value <= 9 )
			{
				utf16_string[ string_index++ ] = (uint16_t) '0' + byte_value;
			}
			else
			{
				utf16_string[ string_index++ ] = (uint16_t) 'a' + byte_value;
			}
			byte_shift -= 4;
		}
		while( byte_shift > 0 );

		utf16_string[ string_index++ ] = (uint16_t) ')';

		utf16_string[ string_index++ ] = 0;
	}
	return( 1 );
}

/* Converts the FAT date and time into an UTF-32 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfdatetime_fat_date_time_copy_to_utf32_string(
     libfdatetime_fat_date_time_t *fat_date_time,
     uint32_t *utf32_string,
     size_t utf32_string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error )
{
	libfdatetime_date_time_values_t date_time_values;

	libfdatetime_internal_fat_date_time_t *internal_fat_date_time = NULL;
	static char *function                                         = "libfdatetime_fat_date_time_copy_to_utf32_string";
	size_t string_index                                           = 0;
	uint8_t byte_value                                            = 0;
	uint8_t byte_shift                                            = 0;
	int result                                                    = 0;

	if( fat_date_time == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid FAT date time.",
		 function );

		return( -1 );
	}
	internal_fat_date_time = (libfdatetime_internal_fat_date_time_t *) fat_date_time;

	if( libfdatetime_fat_date_time_copy_to_date_time_values(
	     internal_fat_date_time,
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
		 "%s: unable to set UTF-32 string.",
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
		if( utf32_string_size < 16 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: string is too small.",
			 function );

			return( -1 );
		}
		utf32_string[ string_index++ ] = (uint32_t) '(';
		utf32_string[ string_index++ ] = (uint32_t) '0';
		utf32_string[ string_index++ ] = (uint32_t) 'x';

		byte_shift = 12;

		do
		{
			byte_value = ( internal_fat_date_time->date >> byte_shift ) & 0x0f;

			if( byte_value <= 9 )
			{
				utf32_string[ string_index++ ] = (uint32_t) '0' + byte_value;
			}
			else
			{
				utf32_string[ string_index++ ] = (uint32_t) 'a' + byte_value;
			}
			byte_shift -= 4;
		}
		while( byte_shift > 0 );

		utf32_string[ string_index++ ] = (uint32_t) ' ';
		utf32_string[ string_index++ ] = (uint32_t) '0';
		utf32_string[ string_index++ ] = (uint32_t) 'x';

		byte_shift = 12;

		do
		{
			byte_value = ( internal_fat_date_time->time >> byte_shift ) & 0x0f;

			if( byte_value <= 9 )
			{
				utf32_string[ string_index++ ] = (uint32_t) '0' + byte_value;
			}
			else
			{
				utf32_string[ string_index++ ] = (uint32_t) 'a' + byte_value;
			}
			byte_shift -= 4;
		}
		while( byte_shift > 0 );

		utf32_string[ string_index++ ] = (uint32_t) ')';

		utf32_string[ string_index++ ] = 0;
	}
	return( 1 );
}

