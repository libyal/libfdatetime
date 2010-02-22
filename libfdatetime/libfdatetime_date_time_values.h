/*
 * Date and time values functions
 *
 * Copyright (c) 2010, Joachim Metz <jbmetz@users.sourceforge.net>
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

#if !defined( _LIBFDATETIME_DATE_TIME_VALUES_H )
#define _LIBFDATETIME_DATE_TIME_VALUES_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libfdatetime_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfdatetime_date_time_values libfdatetime_date_time_values_t;

struct libfdatetime_date_time_values
{
	/* The year
	 */
	uint16_t year;

	/* The month
	 * 1 represents January
	 */
	uint8_t month;

	/* The day of the month
	 */
	uint8_t day;

	/* The hour in 24 hour format
	 * so 13 represents 1 PM
	 */
	uint8_t hours;

	/* The minutes
	 */
	uint8_t minutes;

	/* The seconds
	 */
	uint8_t seconds;
};

int libfdatetime_date_time_values_get_string_size(
     libfdatetime_date_time_values_t *date_time_values,
     size_t *string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error );

int libfdatetime_date_time_values_copy_to_utf8_string(
     libfdatetime_date_time_values_t *date_time_values,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error );

int libfdatetime_date_time_values_copy_to_utf16_string(
     libfdatetime_date_time_values_t *date_time_values,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error );

int libfdatetime_date_time_values_copy_to_utf32_string(
     libfdatetime_date_time_values_t *date_time_values,
     uint32_t *utf32_string,
     size_t utf32_string_size,
     uint8_t string_format_flags,
     int date_time_format,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

