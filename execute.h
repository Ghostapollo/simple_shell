#ifndef EXECUTE_H
#define EXECUTE_H

#include "shell.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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
			if (strcmp(args[0], "cd") == 0)
			{
				if (chdir(args[1]) != 0)
				{
					perror(args[1]);
				}
				exit(EXIT_SUCCESS);
			}
			else
			{
				perror("execvp");
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		wait(NULL);
	}
	return (1);
}

#endif
