/* this file belongs to `printable` http://github.com/amery/printable
 *
 * Copyright (c) 2010, Alejandro Mery <amery@geeks.cl>
 * All rights reserved. See COPYING for details.
 ***/

#include "printable.h"
#include "echo_encode.h"

#define CEC "abtnvfr"

size_t echo_encode(uint8_t c, uint8_t peek, char *out, unsigned flags)
{
	if (c == '\n' && flags & SKIP_NL)
		goto raw;

	if (c > 0x1f && c < 0x7f) { /* ASCII printable characters */
		switch(c) {
		case '"':
		case '\'':
		case '\\':
			goto escape2;
		default:
raw:
			if (out) { out[0] = c; }
			return 1;
		}
	} else if (c >= '\a' && c <= '\r') {  /* C Character Escape Codes */
		c = CEC[c - '\a'];
		goto escape2;
	} else { /* not printable, octal encoded as \0num */
		int nc;

		char o[3] = {
			'0' + ((c & (0x07 << 6)) >> 6),
			'0' + ((c & (0x07 << 3)) >> 3),
			'0' + ((c & (0x07 << 0)) >> 0)
		};

		if (out) {
			out[0] = '\\';
			out[1] = '0';
		}

		if (peek >= '0' && peek <= '9')
			nc = 5;
		else if (o[0] != '0')
			nc = 5;
		else if (o[1] != '0')
			nc = 4;
		else if (o[2] != '0')
			nc = 3;
		else
			nc = 2;

		if (out) {
			register int i, j;
			for (i=2, j=5-nc; i < nc; i++, j++)
				out[i] = o[j];
		}

		return nc;
	}
escape2:
	if (out) { out[0] = '\\'; out[1] = c; }
	return 2;
}
