/* this file belongs to `printable` http://github.com/amery/printable
 *
 * Copyright (c) 2010, Alejandro Mery <amery@geeks.cl>
 * All rights reserved. See COPYING for details.
 ***/

#include "printf_encode.h"

#define hexa "0123456789abcdef"
#define CEC "abtnvfr"

size_t printf_encode(uint8_t c, char *out)
{
	if (c > 0x1f && c < 0x7f) { /* ASCII printable characters */
		switch(c) {
		case '"':
		case '\\':
			goto escape2;
		default:
			if (out) { out[0] = c; }
			return 1;
		}
	} else if (c >= '\a' && c <= '\r') {  /* C Character Escape Codes */
		c = CEC[c - '\a'];
		goto escape2;
	} else if (c == 0) {
		c = '0';
		goto escape2;
	} else { /* not printable, hexa encoded */
		if (out) {
			out[0] = '\\';
			out[1] = 'x';
			out[2] = hexa[(c & (0x0f << 4)) >> 4];
			out[3] = hexa[c & 0x0f];
		}

		return 4;
	}
escape2:
	if (out) { out[0] = '\\'; out[1] = c; }
	return 2;
}
