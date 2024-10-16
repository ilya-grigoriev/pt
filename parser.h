#ifndef PARSER_H
#define PARSER_H
typedef struct {
	unsigned int lines_count;
	char **lines;
} Slide;
#endif

int get_num_slides(char *filepath);
int get_max_num_lines_in_slide(char *filepath);
void parse_file(char *filepath, Slide *slides);
