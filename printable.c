#include <unistd.h>
#include <errno.h>

#include <stdio.h>

#include "printf_encoded.h"

int main(int argc, char **argv)
{
	char buffer[4096];
	ssize_t l;

	/* zero indicates EOF */
	while ((l = read(STDIN_FILENO, buffer, sizeof(buffer))) != 0) {
		if (l > 0) {
			print_printf_encoded(STDOUT_FILENO, buffer, l);
		} else if (errno == EAGAIN || errno == EINTR) {
			continue;
		} else {
			perror("read(stdin)");
			return -1;
		}
	}
	return 0;
}
