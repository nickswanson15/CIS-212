#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ADTs/queue.h"

#define UNUSED __attribute__((unused))

void printQueue(const Queue *ql, FILE *fp) {

	const Iterator *it;
	it = ql->itCreate(ql);

	if (it == NULL) {
		fprintf(stdout, "Empty\n");
	}

	else {
		while (it->hasNext(it)) {
			long temp;
			(void) it->next(it, (void **)&temp);

			if (it->hasNext(it)) {
				fprintf(fp, "%ld ", temp);
			}

			else {
				fprintf(fp, "%ld", temp);
			}
		}
		it->destroy(it);
		fprintf(stdout, "\n");
	}
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

	const Queue *ql = Queue_create(doNothing);
	if(ql == NULL) {
		fprintf(stderr, "Unable to create queue\n");
		return EXIT_FAILURE;
	}
	
	while(fgets(buf, sizeof(buf), fd) != NULL) {

		sscanf(buf, "%s", command);

		if(strcmp(command, "enqueue") == 0) {
			long integer;
			sscanf(buf, "%s %ld", command, &integer);
			ql->enqueue(ql, ADT_VALUE(integer));
		}
		if(strcmp(command, "dequeue") == 0) {
			long value;
			if(ql->isEmpty(ql)) {
				fprintf(stdout, "QueueError\n");
			}
			else {
				ql->dequeue(ql, ADT_ADDRESS(&value));
				fprintf(stdout, "%ld\n", value);
			}
		}
		if(strcmp(command, "print") == 0){
			printQueue(ql, stdout);
		}

	}
	ql->destroy(ql);
	fclose(fd);
	return EXIT_SUCCESS;
}
