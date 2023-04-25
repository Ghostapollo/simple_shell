#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * _execute - executes a command with the given arguments
 * @args: the arguments to the command
 * @envp: the environment variables
 *
 * Return: 1 if the command was executed successfully, 0 otherwise
 */
int _execute(char **args, char **envp)
{
	if (_strcmp(args[0], "exit") == 0)
	{
		if (args[1])
		{
			int status = atoi(args[1]);
			exit(status);
		}
		exit(0);
	}
	else if (_strcmp(args[0], "cd") == 0)
	{
		if (chdir(args[1]) != 0)
		{
			write(STDERR_FILENO, "cd: No such file or directory\n", 30);
			return (0);
		}
		return (1);
	}
	else if (_strcmp(args[0], "setenv") == 0)
	{
		if (args[1] == NULL || args[2] == NULL || args[3] != NULL)
		{
			write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 29);
			return (0);
		}
		if (setenv(args[1], args[2], 1) != 0)
		{
			write(STDERR_FILENO, "setenv: Failed to set environment variable\n", 44);
			return (0);
		}
		return (1);
	}
	else if (_strcmp(args[0], "unsetenv") == 0)
	{
		if (args[1] == NULL || args[2] != NULL)
		{
			write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 25);
			return (0);
		}
		if (unsetenv(args[1]) != 0)
		{
			write(STDERR_FILENO, "unsetenv: Failed to unset environment variable\n", 49);
			return (0);
		}
		return (1);
	}
}
