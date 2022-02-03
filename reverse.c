#include "stringlist.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define UNUSED __attribute__((unused))
int main(UNUSED int argc, UNUSED char *argv[]) {
	
	char buf[BUFSIZ];
	const StringList *sl = StringList_create(50L);

	if ((sl) == NULL) {
		fprintf(stderr, "Unable to create string list\n");
		return EXIT_FAILURE;
	}

	while(fgets(buf, sizeof buf, stdin) != NULL) {
		char *temp = strdup(buf);
		if(!sl->append(sl, temp)) {
			fprintf(stderr, "Unable to append to string list\n");
			sl->destroy(sl);
			return EXIT_FAILURE;
		}
	}

	int n = sl->size(sl);
	for(int i = n-1; i >= 0L; i--) {
		char *s;
		(void)sl->get(sl, i, (char **)&s);
		printf("%s", s);
	}
	sl->destroy(sl);
	return EXIT_SUCCESS;
}


		

