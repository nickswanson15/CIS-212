#include <stdio.h>
#include <stdlib.h>

#define UNUSED __attribute__((unused))

int main(UNUSED int argc,  UNUSED char *argv[]) {
	long nchars =0L;
	char buf[BUFSIZ];
	int exitStatus = EXIT_SUCCESS;


	while (fgets(buf, sizeof buf, stdin) != NULL) {

		for (int i = 0; buf[i] != '\0'; i++) {
			nchars++;
		}
		

	}

	printf("%8ld\n", nchars);
	return exitStatus;
}

