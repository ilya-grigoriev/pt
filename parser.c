#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int get_num_slides(char *filepath);

int parse_file(char *filepath, char ***slides) 
{
	int slides_n = get_num_slides(filepath);
	char *slide = malloc(sizeof(char *));

	*slides = malloc(sizeof(slide) * slides_n);
	char **slides_start_position = *slides;

	FILE *file = fopen(filepath, "r");
	char *line = NULL;
	size_t len = 0; // for get all line
	while (getline(&line, &len, file) != -1) {
		if (strcmp(line, "\n") != 0)
			strcpy(slide, line);
		else {
			**slides = malloc(sizeof(slide));
			strcpy(**slides, slide);
			(*slides)++;
		}
	}

	if (strcmp(slide, "\n") != 0) {
			**slides = malloc(sizeof(slide));
			strcpy(**slides, slide);
	}

	free(slide);
	fclose(file);
	*slides = slides_start_position;
	
	return slides_n;
}

int get_num_slides(char *filepath) 
{
	FILE *file = fopen(filepath, "r");

	int blanklines = 0;
	char *line = NULL;
	size_t len = 0;
	while (getline(&line, &len, file) != -1)
		if (strcmp(line, "\n") == 0)
			blanklines++;	
	fclose(file);
	return blanklines + 1;
}
