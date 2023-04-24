#include "main.h"
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
	ssize_t buffer_size = 0;

	if (getline(&line, &buffer_size, stdin) == -1)
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

/**
 * _execute - executes a command with the given arguments
 * @args: the arguments to the command
 *
 * Return: 1 if the command was executed successfully, 0 otherwise
 */
int _execute(char **args)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}

	return (1);
}

/**
 * main - entry point for the program
 *
 * Return: always 0
 */
int main(void)
{
	char *line = NULL;
	char *args[BUFFER_SIZE];
	int num_args = 0;
	char *path = "/bin:/usr/bin";
	
	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		line = _get_line();
		if (line == NULL)
			break;
		num_args = _parse_line(line, args);
		if (num_args > 0)
			_execute(args);
		free(line);
	}

	return (0);
}
