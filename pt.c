#include <ncurses.h>
#include <string.h>
#include "parser.h"

static char **slides;

int main(int argc, char *argv[])
{
	initscr();
	curs_set(0);
	noecho();

	int max_slides_n = parse_file("test", &slides);
	int cur_slides_n = 1;

	int c;
	do {
		switch (c) {
			case 'l':
				cur_slides_n += (cur_slides_n + 1 <= max_slides_n) ? 1 : 0;
				break;
			case 'h':
				cur_slides_n -= (cur_slides_n - 1 > 0) ? 1 : 0;
				break;
		}

		mvprintw(10, 10, "%s", *(slides+cur_slides_n-1));
	} while ((c = getch()) != 'q');
	endwin();
	curs_set(1);
}
