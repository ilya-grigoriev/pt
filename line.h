#ifndef PARSER_H
#define PARSER_H
typedef struct line {
	unsigned int num_lines;
	unsigned int num_slides;
	char *content;
	struct line *next_line;
} Line;
#endif

void add_line(Line *lines, char *line);
Line* move_to_end(Line *lines);
int get_max_slides(Line *lines);
void print_lines(Line *lines, int cur_num_slide);
