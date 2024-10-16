#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parser.h"

char *check_args(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	check_args(argc, argv);
	char *filepath = argv[1];

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
		int start = 10;
		for (int i = 0; i < slides[cur_slide_ind].lines_count; i++, start++) {
			mvprintw(start, 10, "%s", slides[cur_slide_ind].lines[i]);
		}
		refresh();
	} while ((c = getch()) != 'q');
	endwin();
	curs_set(1);
}

char *check_args(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "need filepath\n");
		exit(1);
	}

	if (access(argv[1], F_OK) != 0) {
		fprintf(stderr, "file doesn't exist\n");
		exit(1);
	}
}
