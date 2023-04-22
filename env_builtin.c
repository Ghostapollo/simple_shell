#include main.h
#include <stddef.h>

/**
 * _env - prints the current environment
 *
 * Return: always 1
 */

int _env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (1);
}
