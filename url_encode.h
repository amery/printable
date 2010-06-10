/* this file belongs to `printable` http://github.com/amery/printable
 *
 * Copyright (c) 2010, Alejandro Mery <amery@geeks.cl>
 * All rights reserved. See COPYING for details.
 ***/

#ifndef _URL_ENCODE_H
#define _URL_ENCODE_H

#include <stddef.h>
#include <stdint.h>

size_t url_encode(uint8_t c, char *out);

#endif
