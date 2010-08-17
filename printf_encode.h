/* this file belongs to `printable` http://github.com/amery/printable
 *
 * Copyright (c) 2010, Alejandro Mery <amery@geeks.cl>
 * All rights reserved. See COPYING for details.
 ***/

#ifndef _PRINTF_ENCODE_H
#define _PRINTF_ENCODE_H

#include <stddef.h>
#include <stdint.h>

size_t printf_encode(uint8_t c, uint8_t peek, char *out, unsigned flags);

#endif
