#include <unistd.h>
#include <getopt.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>

#include "printf_encode.h"
#include "echo_encode.h"

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

typedef size_t (*encoder) (uint8_t c, char *buf);

static void print_encoded(const char *string, size_t len, encoder f)
{
	char buf[] = "?????"; /* max \0377 */
	while (len > 0) {
		uint8_t c = *string++ & 0xff; len--;
		size_t l = f(c, buf);

		stdout_all(buf, l);
	}
}

static inline void print_stdin_encoded(encoder f)
{
	char buffer[4096];
	ssize_t l;

	/* zero indicates EOF */
	while ((l = read(STDIN_FILENO, buffer, sizeof(buffer))) != 0) {
		if (l > 0) {
			print_encoded(buffer, l, f);
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

	while ((opt = getopt(argc, argv, "e")) != -1) {
		switch (opt) {
		case 'e': f = echo_encode; break;
		default:
			fprintf(stderr,
				 "Usage: %s [-e] [<strings> ...]\n\n"
				 "(stdin is used if no string is given)\n",
				 argv[0]);
			 return(1);
		}
	}

	if (optind < argc) { /* by argument */
		for(int i = optind; i < argc; i++) {
			print_encoded(argv[i], strlen(argv[i]), f);
			stdout_all("\n",1);
		}
	} else {
		print_stdin_encoded(f);
	}
	return 0;
}
