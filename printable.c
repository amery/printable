/* this file belongs to `printable` http://github.com/amery/printable
 *
 * Copyright (c) 2010, Alejandro Mery <amery@geeks.cl>
 * All rights reserved. See COPYING for details.
 ***/

#include <unistd.h>
#include <getopt.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>

#include "printable.h"

#include "printf_encode.h"
#include "echo_encode.h"
#include "url_encode.h"

#define VERSION "0.1"
#define HOME	"http://github.com/amery/printable"
#define DESCRIPTION "A simple command line encoder"

static inline void stdout_all(const char *string, ssize_t len)
{
	while (len > 0) {
		ssize_t l = write(STDOUT_FILENO, string, len);
		if (l == len)
			return;
		else if (l > 0) {
			len -= l;
			string += l;
		} else if (l < 0 && errno != EAGAIN && errno != EINTR) {
			perror("write");
			_exit(errno);
		}
	}
}

typedef size_t (*encoder) (uint8_t c, char *buf, unsigned flags);

static void print_encoded(const char *string, size_t len, encoder f,
			  unsigned flags)
{
	char buf[] = "?????"; /* max \0377 */
	while (len > 0) {
		uint8_t c = *string++ & 0xff; len--;
		size_t l = f(c, buf, flags);

		stdout_all(buf, l);
	}
}

static inline void print_stdin_encoded(encoder f, unsigned flags)
{
	char buffer[4096];
	ssize_t l;

	/* zero indicates EOF */
	while ((l = read(STDIN_FILENO, buffer, sizeof(buffer))) != 0) {
		if (l > 0) {
			print_encoded(buffer, l, f, flags);
		} else if (errno == EAGAIN || errno == EINTR) {
			continue;
		} else {
			perror("read");
			_exit(errno);
		}
	}
}

int main(int argc, char **argv)
{
	int opt;
	encoder f = printf_encode;

	while ((opt = getopt(argc, argv, "?Vpeu")) != -1) {
		switch (opt) {
		case 'V':
			fputs("printable v" VERSION " <" HOME ">\n"
			      DESCRIPTION "\n"
			      "Copyright (c) 2010, Alejandro Mery <amery@geeks.cl>\n",
			      stderr);
			return 0;
		case 'p': f = printf_encode; break;
		case 'e': f = echo_encode; break;
		case 'u': f = url_encode; break;
		default:
			fprintf(stderr,
				"printable v" VERSION "\n" DESCRIPTION "\n\n"
				 "Usage: %s [-V] [-peu] [<strings> ...]\n\n"
				 "  -V   print version and exit\n"
				 "  -p   encode for printf()\n"
				 "  -e   encode for `echo`\n"
				 "  -u   encode for the querystring of a url\n"
				 "\n(stdin is used if no string is given)\n",
				 argv[0]);
			 return(1);
		}
	}

	if (optind < argc) { /* by argument */
		for(int i = optind; i < argc; i++) {
			print_encoded(argv[i], strlen(argv[i]), f, 0);
			stdout_all("\n",1);
		}
	} else {
		print_stdin_encoded(f, 0);
	}
	return 0;
}
