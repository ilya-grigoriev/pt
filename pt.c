#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "line.h"
#include "parser.h"
#include "config.def.h"
#include "args.h"

#define START_NUM_LINES 0
#define START_NUM_SLIDES 1

#define READ "r"

int main(int argc, char *argv[])
{
	int ind_filepath = check_args(argc, argv);
	char *filepath = argv[ind_filepath];

	initscr();
	curs_set(0);
	noecho();

	FILE *file = fopen(filepath, READ);

	// initialize
	Line *lines = malloc(sizeof(Line));

	parse_file(file, lines, START_NUM_LINES, START_NUM_SLIDES);

	fclose(file);

	int c;
	int max_num_slides = get_max_slides(lines);
	int cur_num_slide = 1;
	do {
		switch (c) {
			case 'l':
				if (cur_num_slide + 1 <= max_num_slides) cur_num_slide++;
				break;
			case 'h':
				if (cur_num_slide - 1 >= 1) cur_num_slide--;
				break;
		}

		erase();
		print_lines(lines, cur_num_slide);
		refresh();
	} while ((c = getch()) != 'q');
	endwin();
	curs_set(1);
}
