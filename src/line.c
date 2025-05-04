#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "line.h"
#include "args.h"

void add_line(Line *lines, char *line)
{
	lines->content = calloc(strlen(line) + 1, sizeof(char));
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

int get_len_line(char *line)
{
	mbstate_t mbs;
	size_t length_symbol;
	wchar_t dest;
	int max = strlen(line);
	int len = 0;

	memset(&mbs, '\0', sizeof(mbs));
	while (max > 0) {
		length_symbol = mbrtowc(&dest, line, max, &mbs);
		if ((length_symbol==0) || (length_symbol>max))
			break;
		line += length_symbol;
		max -= length_symbol;

		len++;
	}
	return len;
}

int get_max_len_line(Line *lines, int cur_num_slide) {
	int max_len = 0;
	int cur_len = 0;
	while (lines->num_slides == cur_num_slide) {
		cur_len = get_len_line(lines->content);
		max_len = (max_len < cur_len) ? cur_len : max_len;
		lines = lines->next_line;
	}

	return max_len;
}


#define Y_NUM_SLIDE LINES-1
#define X_NUM_SLIDE COLS-3
void print_lines(Line *lines, int cur_num_slide)
{
	lines = skip_slides(lines, cur_num_slide);
	
	mvprintw(Y_NUM_SLIDE, X_NUM_SLIDE, "%d", cur_num_slide);

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
