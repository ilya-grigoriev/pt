#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int main(int argc, char *argv[])
{
	initscr();
	curs_set(0);
	noecho();

	int slides_n = get_num_slides("test");
	Slide *slides;
	parse_file("test", slides);

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
