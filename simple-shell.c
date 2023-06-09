#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define DELIMITERS " \t\r\n\a"

/**
 * _get_line - reads a line of input from stdin
 *
 * Return: a pointer to the line read, or NULL on failure or end of file
 */
char *_get_line(void)
{
	char *line = NULL;
	size_t buffer_size = 0;

	if (getline(&line, (size_t*)&buffer_size, stdin) == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}

/**
 * _parse_line - tokenizes a line of input into an array of arguments
 * @line: the line to parse
 * @args: a pointer to an array of pointers to store the arguments
 *
 * Return: the number of arguments parsed
 */
int _parse_line(char *line, char **args)
{
	int num_args = 0;
	char *token;

	token = strtok(line, DELIMITERS);
	while (token != NULL)
	{
		args[num_args++] = token;
		token = strtok(NULL, DELIMITERS);
	}
	args[num_args] = NULL;

	return (num_args);
}
