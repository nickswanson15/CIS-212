#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ADTs/stack.h"

#define UNUSED __attribute__((unused))

void printStack(const Stack *st, FILE *fp) {
	long length;
	void **theArray = st->toArray(st, &length);

	if(theArray == NULL) {
		fprintf(stdout, "Empty\n");
	}

	else {
		for(int i = 0; i < length; i++) {
			if (i == 0) {
				fprintf(fp, "%ld", (long)theArray[i]);
			}
			else {
				fprintf(fp, " %ld", (long)theArray[i]);
			}
		}
		fprintf(stdout, "\n");
	}
	free(theArray);
}

int main(UNUSED int argc, UNUSED char *argv[]) {
	
	if (argc != 2) {
		fprintf(stderr, "usage: %s file\n", argv[0]);
		return EXIT_FAILURE;
	}

	FILE *fd;
	fd = fopen(argv[1], "r");
	if(fd == NULL) {

		fprintf(stderr, "%s: open (%s) error\n", argv[0], argv[1]);
		return EXIT_FAILURE;
	}

	char buf[BUFSIZ];
	char command[BUFSIZ];
	long size;

	fgets(buf, sizeof(buf), fd);
	sscanf(buf, "%ld", &size);

	const Stack *st = Stack_create(doNothing);
	if(st == NULL) {
		fprintf(stderr, "Unable to create stack\n");
		return EXIT_FAILURE;
	}
	
	while(fgets(buf, sizeof(buf), fd) != NULL) {

		sscanf(buf, "%s", command);

		if(strcmp(command, "push") == 0) {
			long integer;
			sscanf(buf, "%s %ld", command, &integer);
			st->push(st, ADT_VALUE(integer));
		}
		if(strcmp(command, "pop") == 0) {
			long value;
			if(st->isEmpty(st)) {
				fprintf(stdout, "StackError\n");
			}
			else {
				st->pop(st, ADT_ADDRESS(&value));
				fprintf(stdout, "%ld\n", value);
			}
		}
		if(strcmp(command, "print") == 0){
			printStack(st, stdout);
		}

	}
	st->destroy(st);
	fclose(fd);
	return EXIT_SUCCESS;
}
