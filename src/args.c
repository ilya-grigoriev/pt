#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "args.h"
#include "margin.h"

int is_center = 0;

int is_value_exists(int cur_ind, int argc);
void raise_error(char *message);
int is_str_like_int(char *n);

#define INDEFINITE_INDEX 0
int check_args(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "need filepath\n");
		exit(1);
	}

	int ind_filepath = INDEFINITE_INDEX;
	for (int ind = 1; ind < argc; ind++)
		if (strcmp(argv[ind], "-c") == 0)
			if (is_value_exists(ind, argc))
				if (is_str_like_int(argv[ind+1]))
					sscanf(argv[++ind], "%d", &cols_margin);
				else
					raise_error("incorrect value for columns\n");
			else
				raise_error("no value for columns\n");
		else if (strcmp(argv[ind], "-r") == 0)
			if (is_value_exists(ind, argc))
				if (is_str_like_int(argv[ind+1]))
					sscanf(argv[++ind], "%d", &rows_margin); 
				else
					raise_error("incorrect value for rows\n");
			else
				raise_error("no value for rows\n");
		else if (strcmp(argv[ind], "-h") == 0 || strcmp(argv[ind], "--help") == 0) {
			printf("usage: pt [-c <value>] [-r <value>] [-cen] [--center] [-h] [--help] filepath\n");
			exit(0);
		}
		else if (strcmp(argv[ind], "-cen") == 0 || strcmp(argv[ind], "--center") == 0)
			is_center = 1;
		else if (access(argv[ind], F_OK) != 0)
			raise_error("file doesn't exist\n");
		else
			ind_filepath = ind;

	if (ind_filepath == INDEFINITE_INDEX) {
		fprintf(stderr, "file isn't provided\n");
		exit(1);
	}

	return ind_filepath;
}

int is_value_exists(int cur_ind, int argc)
{
	return cur_ind + 1 < argc;
}

void raise_error(char *message)
{
	fprintf(stderr, message);
	exit(1);
}

int is_str_like_int(char *n) {
	return atoi(n) > 0;
}
