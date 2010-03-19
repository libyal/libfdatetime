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

#if !defined( _LIBFDATETIME_INTERNAL_NSF_TIMEDATE_H )
#define _LIBFDATETIME_INTERNAL_NSF_TIMEDATE_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libfdatetime_extern.h"
#include "libfdatetime_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfdatetime_internal_nsf_timedate libfdatetime_internal_nsf_timedate_t;

/* Contains a 64-bit value which consists of:
 * The lower 32-bit value represents the amount of 100th seconds
 * The upper 32-bit value which consists of:
 * a 24-bit value which contains the amount of Julian day
 * a 4-bit value which contains the UTC timezone difference in hours
 * a 2-bit value which contains the UTC timezone difference in 15 minutes periods
 * a 1-bit value to indicate if the timezone difference is negative (0) or positive (1)
 * a 1-bit value to indicate if the day light savings are active
 */
struct libfdatetime_internal_nsf_timedate
{
	/* The lower nsf timedate part
	 */
	uint32_t lower;

	/* The upper nsf timedate part
	 */
	uint32_t upper;
};

LIBFDATETIME_EXTERN int libfdatetime_nsf_timedate_initialize(
                         libfdatetime_nsf_timedate_t **nsf_timedate,
                         liberror_error_t **error );

LIBFDATETIME_EXTERN int libfdatetime_nsf_timedate_free(
                         libfdatetime_nsf_timedate_t **nsf_timedate,
                         liberror_error_t **error );

LIBFDATETIME_EXTERN int libfdatetime_nsf_timedate_copy_from_byte_stream(
                         libfdatetime_nsf_timedate_t *nsf_timedate,
                         uint8_t *byte_stream,
                         size_t byte_stream_size,
                         uint8_t byte_order,
                         liberror_error_t **error );

LIBFDATETIME_EXTERN int libfdatetime_nsf_timedate_copy_from_uint64(
                         libfdatetime_nsf_timedate_t *nsf_timedate,
                         uint64_t value_64bit,
                         liberror_error_t **error );

int libfdatetime_nsf_timedate_copy_to_date_time_values(
     libfdatetime_internal_nsf_timedate_t *internal_nsf_timedate,
     libfdatetime_date_time_values_t *date_time_values,
     liberror_error_t **error );

LIBFDATETIME_EXTERN int libfdatetime_nsf_timedate_get_string_size(
                         libfdatetime_nsf_timedate_t *nsf_timedate,
                         size_t *string_size,
                         uint8_t string_format_flags,
                         int date_time_format,
                         liberror_error_t **error );

LIBFDATETIME_EXTERN int libfdatetime_nsf_timedate_copy_to_utf8_string(
                         libfdatetime_nsf_timedate_t *nsf_timedate,
                         uint8_t *utf8_string,
                         size_t utf8_string_size,
                         uint8_t string_format_flags,
                         int date_time_format,
                         liberror_error_t **error );

LIBFDATETIME_EXTERN int libfdatetime_nsf_timedate_copy_to_utf16_string(
                         libfdatetime_nsf_timedate_t *nsf_timedate,
                         uint16_t *utf16_string,
                         size_t utf16_string_size,
                         uint8_t string_format_flags,
                         int date_time_format,
                         liberror_error_t **error );

LIBFDATETIME_EXTERN int libfdatetime_nsf_timedate_copy_to_utf32_string(
                         libfdatetime_nsf_timedate_t *nsf_timedate,
                         uint32_t *utf32_string,
                         size_t utf32_string_size,
                         uint8_t string_format_flags,
                         int date_time_format,
                         liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

