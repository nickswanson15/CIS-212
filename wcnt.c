#include <stdio.h>
#include <stdlib.h>
#include "stsplit.h"

#define UNUSED __attribute__((unused))

int main(UNUSED int argc,  UNUSED char *argv[]) {
	long nwords =0L;
	char buf[BUFSIZ];
	int exitStatus = EXIT_SUCCESS;



	while (fgets(buf, sizeof buf, stdin) != NULL) {

		int i = 0;
		
		while (stsplit(buf)[i] != NULL){
			nwords++;
			i++;
		}
		
		stfree(stsplit(buf));

	}

	printf("%8ld\n", nwords);
	return exitStatus;
}

