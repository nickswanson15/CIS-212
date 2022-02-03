#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ADTs/stack.h"

#define UNUSED __attribute__((unused))

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
	char *current;
	long size;

	fgets(buf, sizeof(buf), fd);
	sscanf(buf, "%ld", &size);

	while((current = fgets(buf, sizeof(buf), fd)) != NULL) {

		bool answer = true;

		int n = strlen(current) - 1;

		const Stack *st = Stack_create(doNothing);
		if(st == NULL) {
			fprintf(stderr, "Unable to create stack\n");
			return EXIT_FAILURE;
		}

		for(int i = 0; i < n; i++) {

			if((buf[i] == '(') || (buf[i] == '[') || (buf[i] == '{') || (buf[i] == '<')) {
				st->push(st, ADT_VALUE(buf[i]));
			}
			if((buf[i] == ')') || (buf[i] == ']') || (buf[i] == '}') || (buf[i] == '>')) {
				if(st->isEmpty(st)){
					answer = false;
					break;
				}
				else {
					char tmp;
					st->pop(st, ADT_ADDRESS(&tmp));
					if((buf[i] == ')') && (tmp != '(')) {
						answer = false;
						break;
					}
					if((buf[i] == ']') && (tmp != '[')) {
						answer = false;
						break;
					}
					if((buf[i] == '}') && (tmp != '{')) {
						answer = false;
						break;
					}
					if((buf[i] == '>') && (tmp != '<')) {
						answer = false;
						break;
					}
				}
			}
		}
		if (!(st->isEmpty(st))) {
			answer = false;
		}
		if (answer == true) {
			fprintf(stdout, "YES\n");
		}
		else {
			fprintf(stdout, "NO\n");
		}
		st->destroy(st);
	}

	fclose(fd);
	return EXIT_SUCCESS;
}
