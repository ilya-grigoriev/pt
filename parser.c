#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "line.h"
#include "parser.h"

#define ALL_LINE 0

int is_new_slide = 0;

void parse_file(FILE *file, Line *lines, int cur_num_lines, int cur_num_slides) 
{
	char *line;
	
	line = skip_blanklines(&file);

	if (is_text(line) != 1)
		return;

	if (is_new_slide) {
		cur_num_slides++;
		cur_num_lines = 1;
		is_new_slide = 0;
	}
	else
		cur_num_lines++;

	lines->num_slides = cur_num_slides;
	lines->num_lines = cur_num_lines;
	lines->next_line = malloc(sizeof(Line));

	add_line(lines, line);

	parse_file(file, lines->next_line, cur_num_lines, cur_num_slides);
}

char *skip_blanklines(FILE **file)
{
	char *line = NULL;
	size_t len = ALL_LINE;
	while (getline(&line, &len, *file) != -1)
		if (is_text(line) != 1) {
			is_new_slide = 1;
			continue;
		}
		else
			break;
	return line;
}

int is_text(char *line)
{
	for (int ind = 0; ind < strlen(line); ind++) {
		if (isalnum(line[ind]))
			return 1;
	}
	return 0;
}
