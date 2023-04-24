#include <stdlib.h>
#include "main.h"

/**
 * exit_shell - exits the simple shell program
 * @argv: argument vector
 * Return: Always returns 0
 */
int exit_shell(char **argv)
{
	(void)argv;
	exit(EXIT_SUCCESS);
	return (0);
}
