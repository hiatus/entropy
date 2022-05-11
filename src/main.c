#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "entropy.h"
#include "shannon.h"

const char banner[] = "entropy [file]..\n";

int main(int argc, char **argv)
{
	FILE *in;

	ssize_t len;
	unsigned char buffer[ENTROPY_BUFF_SIZE];

	shannon_init();

	if (argc == 1) {
		while ((len = read(STDIN_FILENO, buffer, ENTROPY_BUFF_SIZE)))
			shannon_update(buffer, len);

		goto out;
	}

	if (! strcmp(argv[1], "-h") || ! strcmp(argv[1], "--help")) {
		fputs(banner, stderr);
		return 0;
	}

	for (int i = 1; i < argc; ++i) {
		if (access(argv[i], F_OK | R_OK)) {
			fprintf(
				stderr,	"[access] Cannot read '%s': %s\n",
				argv[i], strerror(errno)
			);

			return 1;
		}
	}

	for (int i = 1; i < argc; ++i) {
		if (! (in = fopen(argv[i], "rb"))) {
			fprintf(
				stderr, "[fopen] Failed to open '%s': %s\n",
				argv[i], strerror(errno)
			);

			continue;
		}

		while ((len = fread(buffer, 1, ENTROPY_BUFF_SIZE, in)) > 0)
			shannon_update(buffer, len);

		fclose(in);
	}
out:
	printf("%.5f\n", shannon_entropy());
	return 0;
}
