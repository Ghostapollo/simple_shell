#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 * check_command - checks if a command exists
 * @args: The command and its arguments
 * @path: The PATH environment variable
 * Return: The path of the command if it exists, NULL otherwise
 */
char *check_command(char **args, char *path)
{
	char *p, *command_path;
	int i;
	
	if (access(args[0], X_OK) == 0)
		return (args[0]);
	
	p = strtok(path, ":");
	
	while (p != NULL)
	{
		command_path = malloc(strlen(p) + strlen(args[0]) + 2);
		sprintf(command_path, "%s/%s", p, args[0]);
	
		if (access(command_path, X_OK) == 0)
			return (command_path);
	
		free(command_path);
		p = strtok(NULL, ":");
	}
	return (NULL);
}

/**
 * execute_command - executes a command
 * @args: The command and its arguments
 * @path: The PATH environment variable
 */
void execute_command(char **args, char *path)
{
	pid_t pid;
	char *command_path;
	int status;
	
	command_path = check_command(args, path);
	if (command_path == NULL)
	{
		write(STDERR_FILENO, args[0], strlen(args[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		exit(EXIT_FAILURE);
	}
	
	pid = fork();
	
	if (pid == 0)
	{
		if (execve(command_path, args, NULL) == -1)
		{
			write(STDERR_FILENO, "Error: Could not execute command\n", 33);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		write(STDERR_FILENO, "Error: Could not create child process\n", 39);
		exit(EXIT_FAILURE);
	}
	else
	{
		{
			do waitpid(pid, &status, WUNTRACED);
		}
		
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
