#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ADTs/stringADT.h"
#include "ADTs/arraylist.h"

int main(int argc, char *argv[]) {

	int opt;
	bool case1, case2;
	extern int opterr;

	case1 = case2 = false;
	opterr = 0;
	while((opt = getopt(argc, argv, "lp")) != -1) {
		switch(opt) {
			case 'l': case1 = true; break;
			case 'p': case2 = true; break;
			default:
				fprintf(stderr, "%s: illegal option '-%c'\n", argv[0], optopt);
				fprintf(stderr, "usage: %s [-lp] [FILE]\n", argv[0]);
				return EXIT_FAILURE;
		}
	}

	if ((argc - optind) == 0) {

		char buf[BUFSIZ];
		const String *st = String_create("");
	
		while (fgets(buf, sizeof buf, stdin) != NULL) {

			st->clear(st);
			st->append(st, buf);
			st->rStrip(st);

			if (case1 == true) {
				st->lower(st);
			}

			if (case2 == true) {
				st->translate(st, "[:punct:]", ' ');
			}

			const ArrayList *al = st->split(st, "");
			if (al == NULL) {
				continue;
			}
			const Iterator *it = al->itCreate(al);

			while(it->hasNext(it)) {
				char *temp;
				(void) it->next(it, (void**)&temp);
				printf("%s\n", temp);
			}
			it->destroy(it);
			al->destroy(al);

		}
		st->destroy(st);
	}

	else {	int i;
		int nFiles = 0;
		FILE *fds[50];
		for (i = optind; i <argc; i++) {
			FILE *fd = fopen(argv[i], "r");
			if (fd == NULL){
				fprintf(stderr, "%s: open (%s) error\n", argv[0], argv[i]);
				return EXIT_FAILURE;
			}
			fds[nFiles++] = fd;
		}

		for (i = 0; i < nFiles; i++) {

			char buf[BUFSIZ];
			const String *st = String_create("");
	
			while (fgets(buf, sizeof buf, fds[i]) != NULL) {
				st->clear(st);
				st->append(st, buf);
				st->rStrip(st);

				if (case1 == true) {
					st->lower(st);
				}

				if (case2 == true) {
					st->translate(st, "[:punct:]", ' ');
				}

				const ArrayList *al = st->split(st, "");
				if (al == NULL) {
					continue;
				}
				const Iterator *it = al->itCreate(al);

				while(it->hasNext(it)) {
					char *temp;
					(void) it->next(it, (void**)&temp);
					printf("%s\n", temp);
				}
				it->destroy(it);
				al->destroy(al);

			}
			st->destroy(st);
		}
		for(int i = 0; i < nFiles; i++) {
			fclose(fds[i]);
		}
	}
}
