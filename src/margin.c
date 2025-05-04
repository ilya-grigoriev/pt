#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "margin.h"

int cols_margin = 1;
int rows_margin = 1;

void validate_margins(void)
{
	int max_rows, max_cols;
	getmaxyx(stdscr, max_rows, max_cols);

	cols_margin = (max_cols < cols_margin) ? 1 : cols_margin;
	rows_margin = (max_rows < rows_margin) ? 1 : rows_margin;
}

void process_margins(int argc, char *argv[])
{
	cols_margin = rows_margin = 1;
	for (int ind = 1; ind < argc; ind++)
		if (strcmp(argv[ind], "-c") == 0)
			cols_margin = atoi(argv[++ind]);
		else if (strcmp(argv[ind], "-r") == 0)
			rows_margin = atoi(argv[++ind]);
}
