/* this file belongs to `printable` http://github.com/amery/printable
 *
 * Copyright (c) 2010, Alejandro Mery <amery@geeks.cl>
 * All rights reserved. See COPYING for details.
 ***/

#include "printable.h"
#include "url_encode.h"

#define hex "0123456789ABCDEF"

size_t url_encode(uint8_t c, char *out, unsigned UNUSED(flags))
{
	if (c > 0x1f && c < 0x7f) { /* ASCII printable characters */
		switch (c) {
		case '$': /* reserved */
		case '&':
		case '+':
		case ',':
		case '/':
		case ':':
		case ';':
		case '=':
		case '?':
		case '@':
		case ' ': /* unsafe */
		case '<':
		case '>':
		case '#':
		case '%':
		case '{':
		case '}':
		case '|':
		case '\\':
		case '^':
		case '~':
		case '[':
		case ']':
		case '`':
			break; /* encode */
		default:
			/* raw */
			if (out) { out[0] = c; }
			return 1;
		}
	}

	if (out) {
		out[0] = '%';
		out[1] = hex[(c & (0x0f << 4)) >> 4];
		out[2] = hex[c & 0x0f];
	}
	return 3;
}
