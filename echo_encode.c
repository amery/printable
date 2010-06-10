/* this file belongs to `printable` http://github.com/amery/printable
 *
 * Copyright (c) 2010, Alejandro Mery <amery@geeks.cl>
 * All rights reserved. See COPYING for details.
 ***/
#include "echo_encode.h"

size_t echo_encode(uint8_t c, char *out)
{
	if (c>0x1f && c<0x7f) { /* ASCII printable characters */
		switch(c) {
		case '"':
		case '\'':
		case '\\':
			goto escape2;
		default:
			if (out) { out[0] = c; }
			return 1;
		}
	} else if (c >= '\a' && c <= '\r') {  /* C Character Escape Codes */
		static const char e[] = "abtnvfr";
		c = e[c - '\a'];
		goto escape2;
	} else { /* not printable, octal encoded as \0num */
		char o[3] = {
			'0' + ((c & (0x07 << 6)) >> 6),
			'0' + ((c & (0x07 << 3)) >> 3),
			'0' + ((c & (0x07 << 0)) >> 0)
		};

		if (out) {
			out[0] = '\\';
			out[1] = '0';
		}

		if (o[0] != '0') { /* 3 digit */
			if (out) {
				out[2] = o[0];
				out[3] = o[1];
				out[4] = o[2];
			}
			return 5;
		} else if (o[1] != '0') { /* 2 digit */
			if (out) {
				out[2] = o[1];
				out[3] = o[2];
			}
			return 4;
		} else if (o[2] != '0') { /* 1 digit */
			if (out) {
				out[2] = o[2];
			}
			return 3;
		}
		return 2;
	}
escape2:
	if (out) { out[0] = '\\'; out[1] = c; }
	return 2;
}
