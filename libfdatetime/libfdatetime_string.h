/*
 * Character type string functions
 *
 * Copyright (c) 2006-2010, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _LIBFDATETIME_STRING_H )
#define _LIBFDATETIME_STRING_H

#include <common.h>
#include <narrow_string.h>
#include <types.h>

#include <liberror.h>

#if defined( _cplusplus )
extern "C" {
#endif

/* The internal string type contains UTF-8
 */
typedef uint8_t libfdatetime_character_t;

#define PRIc_LIBFDATETIME	"c"
#define PRIs_LIBFDATETIME	"s"

#define _LIBFDATETIME_STRING( string ) \
	(libfdatetime_character_t *) string

#define libfdatetime_string_snprintf( target, size, format, ... ) \
	narrow_string_snprintf( (char *) target, size, format, __VA_ARGS__ )

#if defined( _cplusplus )
}
#endif

#endif

