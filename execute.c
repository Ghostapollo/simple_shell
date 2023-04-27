#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * tokenize - break a line of input into separate tokens
 *
 * @input: character array to tokenize
 *
 * Return: pointer to array of characters (tokens)
 */
char **tokenize(char *input)
{
	char *token, *dup;
	char **args;
	char *delim = " \n";
	int i;

	args = malloc(sizeof(char *) * 50);
	if (!args)
		return (NULL);
	dup = _strdup(input);
	if (dup == NULL)
		return (NULL);
	i = 0;
	token = strtok(dup, delim);
	while (token != NULL)
	{
		args[i] = malloc(_strlen(token) + 1);
		_strcpy(args[i], token);
		if (args[i] == NULL)
			return (NULL);
		token = strtok(NULL, delim);
		i++;
	}
	args[i] = NULL;
	free(dup);

	return (args);
}

/**
 * executecmd - execute a command with arguments
 *
 * @name: pathname to execute command
 * @argv: array of arguments
 * @env: environment to be passed
 *
 * Return: 0 on success, -1 on failure
 *
 */
int executecmd(const char *name, char *const argv[], char *const env[])
{
	if (fork() == 0)
	{
		if (execve(name, argv, env) == -1)
			return (-1);
	}
	else
	{
		wait(NULL);
	}

	return (0);
}
