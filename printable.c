#include <unistd.h>
#include <errno.h>

#include <stdio.h>

#include "printf_encode.h"

static inline void write_all(int fd, const char *string, ssize_t len)
{
	while (len > 0) {
		ssize_t l = write(fd, string, len);
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

static inline void print_encoded(int fd, const char *string, size_t len)
{
	char buf[] = "?????"; /* max \0377 */
	while (len > 0) {
		uint8_t c = *string++ & 0xff; len--;
		size_t l = printf_encode(c, buf);

		write_all(fd, buf, l);
	}
}

int main(int argc, char **argv)
{
	char buffer[4096];
	ssize_t l;

	/* zero indicates EOF */
	while ((l = read(STDIN_FILENO, buffer, sizeof(buffer))) != 0) {
		if (l > 0) {
			print_encoded(STDOUT_FILENO, buffer, l);
		} else if (errno == EAGAIN || errno == EINTR) {
			continue;
		} else {
			perror("read(stdin)");
			return -1;
		}
	}
	return 0;
}
