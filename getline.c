#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * _getline - a custom implementation of the getline function
 * from the standard library
 *
 * @lineptr: address of the buffer to store the line read
 * @n: length
 * @fd: file descriptor to read from
 *
 * Return: number of characters read
 *
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	const size_t initial = 50, step = 50;
	size_t newsize;
	char *temp, *str;
	size_t num_read = 0;

	if ((lineptr == NULL) || (n == NULL))
		return (-1);
	if (*lineptr == NULL)
	{
		*lineptr = malloc(initial);
		if (*lineptr == NULL)
			return (-1);
		*n = initial;
	}
	str = malloc(sizeof(char));
	while ((read(fd, str, 1)) != EOF)
	{
		num_read++;
		if (num_read >= *n)
		{
			newsize = *n + step;
			temp = _realloc(*lineptr, *n, newsize + 1);
			if (temp != NULL)
				*lineptr = temp, *n = newsize;
			else
				return (-1);
		}

		(*lineptr)[num_read - 1] = *str;
		if (*str == '\n')
			break;
	}
	if (*str == EOF)
		return (-1);
	(*lineptr)[num_read] = '\0';
	free(str);
	return (num_read);
}

/**
 * _realloc - reallocate a memory block
 *
 * @ptr: pointer to the old memory block
 * @old_size: size of the allocated space for ptr
 * @new_size: new size in bytes to allocate
 *
 * Description: contents will be copied to the newly allocate space, starting
 * from ptr to the minimum of old and new sizes. If new_size > old_size, the
 * added memory shoulnot be initialized
 *
 * Return: pointer to the new memory block
 *	   if new_size == old_size, return ptr
 *	   otherwise, return NULL
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;
	unsigned int min_size;

	if (new_size == old_size)
		return (ptr);
	if (new_size <= 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		new_ptr = malloc(new_size);
		if (new_ptr == NULL)
			return (NULL);
		free(ptr);
		return (new_ptr);
	}

	min_size = old_size < new_size ? old_size : new_size;
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	_memcpy(new_ptr, ptr, min_size);

	free(ptr);
	return (new_ptr);
}

/**
 *_memcpy - copy a memory area
 *
 * @dest: pointer to the destination memory
 * @src: pointer to the source memory
 * @n: number of bytes to copy
 *
 * Return: pointer to the destination
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; ++i)
		*(dest + i) = *(src + i);
	return (dest);
}
