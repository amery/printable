/* this file belongs to `printable` http://github.com/amery/printable
 *
 * Copyright (c) 2010, Alejandro Mery <amery@geeks.cl>
 * All rights reserved. See COPYING for details.
 ***/

#ifndef _PRINTABLE_H
#define _PRINTABLE_H

#ifdef UNUSED
#elif defined(__GNUC__)
#	define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#else
#	define UNUSED(x) x
#endif

enum {
	SKIP_NL = 1 << 0,
};

#define VERSION "0.2"
#define HOME	"http://github.com/amery/printable"
#define DESCRIPTION "A simple command line encoder"

#endif
