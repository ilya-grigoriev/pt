#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "line.h"
#include "args.h"

void add_line(Line *lines, char *line)
{
	lines->content = malloc(strlen(line) + 1);
	strcpy(lines->content, line);
}

Line* move_to_end(Line *lines)
{
	while (lines->next_line->content != NULL)
		lines = lines->next_line;
	return lines;	
}

int get_max_slides(Line *lines)
{
	lines = move_to_end(lines);
	return lines->num_slides;
}

void print_lines(Line *lines, int cur_num_slide)
{
	while (lines->num_slides != cur_num_slide)
		lines = lines->next_line;
	
	mvprintw(LINES-1, COLS-3, "%d", cur_num_slide);
	for (int x=rows_margin, y=cols_margin; lines->content != NULL && lines->num_slides == cur_num_slide; x++) {
		mvprintw(x, y, "%s", lines->content);
		lines = lines->next_line;
	}
}
