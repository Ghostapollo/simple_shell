#include "shell.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * printhistory - print history of commands
 *
 * @history: an array of strings containing command history
 *
 */
void printhistory(char **history)
{
	int i;

	for (i = 0; history[i]; ++i)
		printf("%d: %s", i, history[i]);
}

/**
 * updatehistory - update history of commands at the start of the shell
 *
 * @history: the array of strings to hold the history
 * @fd: file descriptor to read from
 *
 */
void updatehistory(char **history, int fd)
{
	char ch;
	int i, j;

	i = 0, j = 0;
	while (read(fd, &ch, 1) >= 0)
	{
		history[i][j] = ch;
		j++;
		if (ch == '\n')
		{
			i++;
			j = 0;
		}
	}
}

/**
 * help - print help for builtins
 *
 * @tokens: command read from the user
 *
 */
void help(char **tokens)
{
	if (tokens[1])
	{
		if (_strcmp(tokens[1], "exit") == 0)
			printf("Usage: exit status\n");
		else if (_strcmp(tokens[1], "env") == 0)
			printf("Usage: env\n");
		else if (_strcmp(tokens[1], "setenv") == 0)
			printf("Usage: setenv VARIABLE VALUE\n");
		else if (_strcmp(tokens[1], "unsetenv") == 0)
			printf("Usage: unsetenv VARIABLE\n");
		else if (_strcmp(tokens[1], "cd") == 0)
			printf("Usage: cd [DIRECTORY]\n");
		else if (_strcmp(tokens[1], "alias") == 0)
			printf("Usage: alias [name[='value'] ...]\n");
		else if (_strcmp(tokens[1], "help") == 0)
			printf("Usage: help [BUILTIN]\n");
		else if (_strcmp(tokens[1], "history") == 0)
			printf("Usage: history\n");
		else
			printf("%s: command not found\n", tokens[1]);
	}
}
