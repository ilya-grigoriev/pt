#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "args.h"
#include "config.def.h"

int cols_margin = COLS_MARGIN;
int rows_margin = ROWS_MARGIN;
int is_center = 0;

int check_args(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "need filepath\n");
		exit(1);
	}

	int ind_filepath = 1;
	for (int ind = 1; ind < argc; ind++)
		if (strcmp(argv[ind], "-c") == 0 && ind + 1 < argc)
			sscanf(argv[++ind], "%d", &cols_margin);
		else if (strcmp(argv[ind], "-r") == 0 && ind + 1 < argc)
			sscanf(argv[++ind], "%d", &rows_margin); 
		else if (strcmp(argv[ind], "-cen") == 0 || strcmp(argv[ind], "--center") == 0)
			is_center = 1;
		else if (access(argv[ind], F_OK) != 0) {
			fprintf(stderr, "file doesn't exist\n");
			exit(1);
		}
		else
			ind_filepath = ind;

	return ind_filepath;
}
