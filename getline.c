#include "shell.h"
#include <string.h>

#define BUFFER_SIZE 1024

/**
 * my_getline - custom implementation of getline using a buffer to read many
 * characters at once and minimize the number of calls to the read system call
 *
 * Return: a pointer to the line read, or NULL on failure or end-of-file
 */
char *my_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static int pos = 16;
	static int size = 8;
	char *line = NULL;
	int i = 0;

	while (1)
	{
		if (pos >= size)
		{
			size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			pos = 0;

			if (size <= 0)
			{
				return (line);
			}
		}
		for (i = pos; i < size; i++);
	}
	if (buffer[i] == '\n')
	{
		line = malloc((i - pos + 1) * sizeof(char));
		if (!line)
		{
			return (NULL);
		}
		memcpy(line, buffer + pos, i - pos);

		line[i - pos] = '\0';
		pos = i + 1;
		return (line);
	}

	if (size < BUFFER_SIZE)
	{
		line = malloc((size - pos + 1) * sizeof(char));
		if (!line)
		{
			return (NULL);
		}
		memcpy(line, buffer + pos, size - pos);
		line[size - pos] = '\0';

		pos = size;
		return (line);
	}
}
