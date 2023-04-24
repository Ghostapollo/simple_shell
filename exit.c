#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

/**
 * exit_shell - Exits the shell program.
 * @argv: The argument vector.
 *
 * Return: Always 0.
 */
int exit_shell(char **argv)
{
	char *exit_msg = "Exiting shell program...\n";
	
	if (strcmp(argv[0], "exit") == 0)
	{
		write(STDOUT_FILENO, exit_msg, strlen(exit_msg));
		exit(EXIT_SUCCESS);
	}
	return (0);
}

