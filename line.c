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

Line *skip_slides(Line *lines, int cur_num_slide) {
	while (lines->num_slides != cur_num_slide)
		lines = lines->next_line;
	return lines;
}

int get_num_slides(Line *lines, int cur_num_slide)
{
	int num = 0;
	while (lines->num_slides == cur_num_slide) {
		num++;
		lines = lines->next_line;
	}

	return num;
}

int get_max_len_line(Line *lines, int cur_num_slide) {
	int max_len = 0;
	while (lines->num_slides == cur_num_slide) {
		max_len = (max_len < strlen(lines->content)) ? strlen(lines->content) : max_len;
		lines = lines->next_line;
	}

	return max_len;
}

void print_lines(Line *lines, int cur_num_slide)
{
	lines = skip_slides(lines, cur_num_slide);
	
	mvprintw(LINES-1, COLS-3, "%d", cur_num_slide);

	int x, y;
	if (is_center) {
		x = (LINES - get_num_slides(lines, cur_num_slide)) / 2;
		y = (COLS - get_max_len_line(lines, cur_num_slide)) / 2;
	}
	else {
		x = rows_margin;
		y = cols_margin;
	}
	for (; lines->content != NULL && lines->num_slides == cur_num_slide; x++) {
		mvprintw(x, y, "%s", lines->content);
		lines = lines->next_line;
	}
}
