#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define READ "r"

char *skip_blanklines(FILE *(*file));
int is_end_of_slide(char *line);
int is_new_slide(Slide *slides);
int is_excess_blankline(char *line, int was_newline);

void add_line(Slide *slides, char *line);
void add_space_for_line(Slide *slides);
void move_to_new_slide(Slide **slides, int *was_newline);

void parse_file(char *filepath, Slide *slides) 
{
	int slides_n = get_num_slides(filepath);

	FILE *file = fopen(filepath, READ);

	char *line = NULL;
	size_t len = 0; // for get all line

	int was_newline = 0;
	
	line = skip_blanklines(&file);

	slides->lines_count = 0;
	if (strcmp(line, "") != 0) {
		slides->lines = malloc(1);
		add_line(slides, line);
	}

	while (getline(&line, &len, file) != -1) {
		if (is_excess_blankline(line, was_newline))
			continue;
		else if (is_end_of_slide(line)) {
			slides->lines -= (slides->lines_count - 1);
			was_newline = 1;
		}
		else {
			if (was_newline)
				move_to_new_slide(&slides, &was_newline);

			if (is_new_slide(slides))
				slides->lines = malloc(1);
			else
				add_space_for_line(slides);

			*(slides->lines) = malloc(sizeof(char*));
			strcpy(*(slides->lines), line);

			slides->lines_count++;
		}
	}

	if (slides->lines_count != 0) {
		slides->lines -= (slides->lines_count - 1);
		slides -= slides_n;
	}

	fclose(file);
}

int get_num_slides(char *filepath) 
{
	FILE *file = fopen(filepath, "r");

	int was_newline = 0;
	int blanklines = 0;
	char *line = NULL;
	size_t len = 0;

	skip_blanklines(&file);

	while (getline(&line, &len, file) != -1)
		if (strcmp(line, "\n") == 0 && was_newline == 1)
			continue;
		else if (strcmp(line, "\n") == 0) {
			blanklines++;	
			was_newline = 1;
		}
		else
			was_newline = 0;

	fclose(file);

	return (blanklines == 0 && was_newline == 0) ? 0 : blanklines;
}

int is_end_of_slide(char *line)
{
	return strcmp(line, "\n") == 0;
}

int is_new_slide(Slide *slides)
{
	return slides->lines_count == 0;
}

int is_excess_blankline(char *line, int was_newline)
{
	return strcmp(line, "\n") == 0 && was_newline == 1;
}

char *skip_blanklines(FILE *(*file))
{
	char *line = NULL;
	size_t len = 0;
	while (getline(&line, &len, *file) != -1)
		if (strcmp(line, "\n") == 0)
			continue;
		else
			break;
	return line;
}

void add_line(Slide *slides, char *line)
{
	*(slides->lines) = malloc(sizeof(char*));
	strcpy(*(slides->lines), line);
	slides->lines_count++;
}

void add_space_for_line(Slide *slides)
{
	slides->lines = realloc(slides->lines, (sizeof slides->lines) * (slides->lines_count + 1));
	slides->lines++;
}

void move_to_new_slide(Slide **slides, int *was_newline)
{
	(*slides)++;
	*was_newline = 0;
	(*slides)->lines_count = 0;
}
