#include <stdlib.h>
#include "line.h"
int get_num_lines(char *filepath);
char *skip_blanklines(FILE *(*file));
int is_text(char *line);
void parse_file(FILE *file, Line *lines, int cur_num_lines, int cur_num_slides);
