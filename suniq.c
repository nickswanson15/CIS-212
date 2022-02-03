#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

#define UNUSED __attribute__((unused))

int main(UNUSED int argc, char *argv[]) {

	int opt;
	bool print1, print2, print3, print4;
	print1 = print2 = print3 = print4 = false;
	opterr = 0;
	while ((opt = getopt(argc, argv, "cdiu")) != -1) {
		switch(opt) {
			case 'c': print1 = true; break;
			case 'd': print2 = true; break;
			case 'i': print3 = true; break;
			case 'u': print4 = true; break;
			default:  fprintf(stderr, "%s: illegal option '-%c'\n", argv[0], optopt);
				  fprintf(stderr, "usage: %s [-cdiu] [FILE] ...\n", argv[0]);
				  return EXIT_FAILURE;
		}
	}

	if (print2 == true && print4 == true) {
		return EXIT_SUCCESS;
	}

	char l[BUFSIZ];
	char c[BUFSIZ];
	char *current;
	int linecount = 1;

	if (argc == optind) {	

		char *last = fgets(l, sizeof l, stdin);

		while((current = fgets(c, sizeof c, stdin)) != NULL) {

			if (print3 == true) {
				if (print1 == true) {
					if (print2 == true) {
						if (strcasecmp(last, current) != 0) {
							if (linecount > 1) {
								printf("%7d"" ""%s", linecount, l);
								strcpy(l, c);
								linecount = 1;
							}

							else {
								strcpy(l, c);
								linecount = 1;
							}
						}

						else {
							linecount += 1;
						}
					}

					if (print4 == true) {
						if (strcasecmp(last, current) != 0) {
							if (linecount < 2) {
								printf("%7d"" ""%s", linecount, l);
								strcpy(l, c);
								linecount = 1;
							}

							else {
								strcpy(l, c);
								linecount = 1;
							}
						}

						else {
							linecount += 1;
						}
					}

					if (print2 == false && print4 == false) {
						if (strcasecmp(last, current) != 0) {
							printf("%7d"" ""%s", linecount, l);
							strcpy(l, c);
							linecount = 1;
						}

						else {
							linecount += 1;
						}
					}
				}

				else {
					
					if (print2 == true) {
						if (strcasecmp(last, current) != 0) {
							if (linecount > 1) {
								printf("%s", l);
								strcpy(l, c);
								linecount = 1;
							}

							else {
								strcpy(l, c);
								linecount = 1;
							}
						}

						else {
							linecount += 1;
						}
					}

					if (print4 == true) {
						if (strcasecmp(last, current) != 0) {
							if (linecount < 2) {
								printf("%s", l);
								strcpy(l, c);
								linecount = 1;
							}

							else {
								strcpy(l, c);
								linecount = 1;
							}
						}

						else {
							linecount += 1;
						}
					}
					
					if (print2 == false && print4 == false) {
						if (strcasecmp(last, current) != 0) {
							printf("%s", l);
							strcpy(l, c);
						}
					}
				}
			}

			else {
				if (print1 == true) {
					if (print2 == true) {
						if (strcmp(last, current) != 0) {
							if (linecount > 1) {
								printf("%7d"" ""%s", linecount, l);
								strcpy(l, c);
								linecount = 1;
							}

							else {
								strcpy(l, c);
								linecount = 1;
							}
						}

						else {
							linecount += 1;
						}
					}

					if (print4 == true) {
						if (strcmp(last, current) != 0) {
							if (linecount < 2) {
								printf("%7d"" ""%s", linecount, l);
								strcpy(l, c);
								linecount = 1;
							}

							else {
								strcpy(l, c);
								linecount = 1;
							}
						}

						else {
							linecount += 1;
						}
					}

					if (print2 == false && print4 == false) {
						if (strcmp(last, current) != 0) {
							printf("%7d"" ""%s", linecount, l);
							strcpy(l, c);
							linecount = 1;
						}

						else {
							linecount += 1;
						}
					}
				}

				else {
					
					if (print2 == true) {
						if (strcmp(last, current) != 0) {
							if (linecount > 1) {
								printf("%s", l);
								strcpy(l, c);
								linecount = 1;
							}

							else {
								strcpy(l, c);
								linecount = 1;
							}
						}

						else {
							linecount += 1;
						}

					}

					if (print4 == true) {
						if (strcmp(last, current) != 0) {
							if (linecount < 2) {
								printf("%s", l);
								strcpy(l, c);
								linecount = 1;
							}

							else {
								strcpy(l, c);
								linecount = 1;
							}
						}

						else {
							linecount += 1;
						}
					}
					
					if (print2 == false && print4 == false) {
						if (strcmp(last, current) != 0) {
							printf("%s", l);
							strcpy(l, c);
						}
					}
				}
			}
		}

		if (print2 == true && linecount > 1) {

			if (print1 == true) {
				printf("%7d"" ""%s", linecount, l);
			}

			else {
				printf("%s", l);
			}
		}

		if (print4 == true && linecount < 2) {

			if (print1 == true) {
				printf("%7d"" ""%s", linecount, l);
			}

			else {
				printf("%s", l);
			}
		}

		if (print2 == false && print4 ==false) {

			if (print1 == true) {
				printf("%7d"" ""%s", linecount, l);
			}

			else {
				printf("%s", l);
			}
		}
	}

	else {
		FILE *fd;
		fd = fopen(argv[optind], "r");
		if (fd == NULL) {
			fprintf(stderr, "%s: open(%s) error\n", argv[0], argv[optind]);
			return EXIT_FAILURE;
		}

		char *last = fgets(l, sizeof l, fd);

		while((current = fgets(c, sizeof c, fd)) != NULL) {

			if (print3 == true) {
				if (print1 == true) {
					if (print2 == true) {
						if (strcasecmp(last, current) != 0) {
							if (linecount > 1) {
								printf("%7d"" ""%s", linecount, l);
								strcpy(l, c);
								linecount = 1;
							}

							else {
								strcpy(l, c);
								linecount = 1;
							}
						}

						else {
							linecount += 1;
						}
					}

					if (print4 == true) {
						if (strcasecmp(last, current) != 0) {
							if (linecount < 2) {
								printf("%7d"" ""%s", linecount, l);
								strcpy(l, c);
								linecount = 1;
							}

							else {
								strcpy(l, c);
								linecount = 1;
							}
						}

						else {
							linecount += 1;
						}
					}

					if (print2 == false && print4 == false) {
						if (strcasecmp(last, current) != 0) {
							printf("%7d"" ""%s", linecount, l);
							strcpy(l, c);
							linecount = 1;
						}

						else {
							linecount += 1;
						}
					}
				}

				else {
					
					if (print2 == true) {
						if (strcasecmp(last, current) != 0) {
							if (linecount > 1) {
								printf("%s", l);
								strcpy(l, c);
								linecount = 1;
							}

							else {
								strcpy(l, c);
								linecount = 1;
							}
						}

						else {
							linecount += 1;
						}
					}

					if (print4 == true) {
						if (strcasecmp(last, current) != 0) {
							if (linecount < 2) {
								printf("%s", l);
								strcpy(l, c);
								linecount = 1;
							}

							else {
								strcpy(l, c);
								linecount = 1;
							}
						}

						else {
							linecount += 1;
						}
					}
					
					if (print2 == false && print4 == false) {
						if (strcasecmp(last, current) != 0) {
							printf("%s", l);
							strcpy(l, c);
						}
					}
				}
			}

			else {
				if (print1 == true) {
					if (print2 == true) {
						if (strcmp(last, current) != 0) {
							if (linecount > 1) {
								printf("%7d"" ""%s", linecount, l);
								strcpy(l, c);
								linecount = 1;
							}

							else {
								strcpy(l, c);
								linecount = 1;
							}
						}

						else {
							linecount += 1;
						}
					}

					if (print4 == true) {
						if (strcmp(last, current) != 0) {
							if (linecount < 2) {
								printf("%7d"" ""%s", linecount, l);
								strcpy(l, c);
								linecount = 1;
							}

							else {
								strcpy(l, c);
								linecount = 1;
							}
						}

						else {
							linecount += 1;
						}
					}

					if (print2 == false && print4 == false) {
						if (strcmp(last, current) != 0) {
							printf("%7d"" ""%s", linecount, l);
							strcpy(l, c);
							linecount = 1;
						}

						else {
							linecount += 1;
						}
					}
				}

				else {
					
					if (print2 == true) {
						if (strcmp(last, current) != 0) {
							if (linecount > 1) {
								printf("%s", l);
								strcpy(l, c);
								linecount = 1;
							}

							else {
								strcpy(l, c);
								linecount = 1;
							}
						}

						else {
							linecount += 1;
						}

					}

					if (print4 == true) {
						if (strcmp(last, current) != 0) {
							if (linecount < 2) {
								printf("%s", l);
								strcpy(l, c);
								linecount = 1;
							}

							else {
								strcpy(l, c);
								linecount = 1;
							}
						}

						else {
							linecount += 1;
						}
					}
					
					if (print2 == false && print4 == false) {
						if (strcmp(last, current) != 0) {
							printf("%s", l);
							strcpy(l, c);
						}
					}
				}
			}
		}

		if (print2 == true && linecount > 1) {

			if (print1 == true) {
				printf("%7d"" ""%s", linecount, l);
			}

			else {
				printf("%s", l);
			}
		}

		if (print4 == true && linecount < 2) {

			if (print1 == true) {
				printf("%7d"" ""%s", linecount, l);
			}

			else {
				printf("%s", l);
			}
		}

		if (print2 == false && print4 == false) {

			if (print1 == true) {
				printf("%7d"" ""%s", linecount, l);
			}

			else {
				printf("%s", l);
			}
		}

		fclose(fd);
	}

	return EXIT_SUCCESS;
}
