#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"
#include <fcntl.h>
#include <stdio.h>

#define MAX_ARGS 10

/**
 * exit_shell - exits the shell
 */
void exit_shell(void)
{
	exit(EXIT_SUCCESS);
}

/**
 * main - the entry point of the program
 * Return: Always 0
 */
int main(void)
{
	char *input;
	char *args[100];
	int num_args;
	int status;

	do {
		prompt();

		int parse_input(char *input, char **args);
		char input[PATH_MAX];
		readlinkat(AT_FDCWD, "simple_shell", input, PATH_MAX);

		char *args[MAX_ARGS];
		num_args = parse_input(input, args);

		if (num_args > 0)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				exit_shell();
			}
			else if (strcmp(args[0], "env") == 0)
			{
				int num_environ_vars = 0;
				char **environ_copy = NULL;
				int i;

			}

			int num_environ_vars = 0;
			char **environ_copy;
			int i;

			for (i = 0; environ[i] != NULL; i++)
				num_environ_vars++;
			environ_copy = malloc(sizeof(char *) * (num_environ_vars + 1));

			for (i = 0; environ[i] != NULL; i++)
				environ_copy[i] = strdup(environ[i]);
			environ_copy[i] = NULL;

			for (i = 0; environ_copy[i] != NULL; i++)
				write(STDOUT_FILENO, environ_copy[i], strlen(environ_copy[i]));
			free(environ_copy);
		}
		else
		{
			if (check_command(args))
			{
				execute_command(args[0]);
			}
			else
			{
				write(STDERR_FILENO, "command not found\n", strlen("command not found\n"));
			}
		}
	}

	while (1); {
		free(input);
	}

	return (0);
}
