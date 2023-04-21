#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_COMMAND_LENGTH 256
#define MAX_ARGUMENTS 10

/**
 * main - Entry point for the simple shell program
 *
 * Return: Always 0 on successful completion
*/
int main(void)
{
	char *line = NULL;
	size_t line_size = 0;
	ssize_t nread;
	int status;
	while (1);

	write(STDOUT_FILENO, "$ ", 2);
	nread = getline(&line, &line_size, stdin);
	if (nread == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
	}
	line[strcspn(line, "\n")] = '\0';
	char *args[MAX_ARGUMENTS + 1];
	char *arg = strtok(line, " ");
	int i = 0;

	while (arg != NULL && i < MAX_ARGUMENTS)
	{
		args[i++] = arg;
		arg = strtok(NULL, " ");
	}
	args[i] = NULL;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (access(args[0], X_OK) == -1)
		{
			write(STDOUT_FILENO, "Command not found: ", 19);
			write(STDOUT_FILENO, args[0], strlen(args[0]));
			write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_FAILURE);
		}
		execve(args[0], args, NULL);
		perror(args[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

return (0);
}
