#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parser.h"
#include "config.def.h"

int check_args(int argc, char *argv[]);

static int cols_margin = COLS_MARGIN;
static int rows_margin = ROWS_MARGIN;

int main(int argc, char *argv[])
{
	int ind_filepath = check_args(argc, argv);
	char *filepath = argv[ind_filepath];

	initscr();
	curs_set(0);
	noecho();

	int slides_n = get_num_slides(filepath);
	Slide *slides;
	parse_file(filepath, slides);

	int c;
	int cur_slide_ind = 0;
	do {
		switch (c) {
			case 'l':
				if (cur_slide_ind + 1 < slides_n) cur_slide_ind++;
				break;
			case 'h':
				if (cur_slide_ind - 1 >= 0) cur_slide_ind--;
				break;
		}

		erase();
		for (int i=0, start=rows_margin; i < slides[cur_slide_ind].lines_count; i++, start++) {
			mvprintw(start, cols_margin, "%s", slides[cur_slide_ind].lines[i]);
		}
		refresh();
	} while ((c = getch()) != 'q');
	endwin();
	curs_set(1);
}

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
		else if (access(argv[ind], F_OK) != 0) {
			fprintf(stderr, "file doesn't exist\n");
			exit(1);
		}
		else
			ind_filepath = ind;

	return ind_filepath;
}
