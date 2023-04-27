#include <stddef.h>
#include "shell.h"
#include <stdlib.h>

/**
 * _strcmp - compare two strings
 * (exactly like the standard libary function)
 *
 * @s1: the first string
 * @s2: the second string
 *
 * Return: 0 if strings are equal otherwise
 * the difference between the strings
 */
int _strcmp(const char *s1, const char *s2)
{
	for (; *s1 != '\0' && *s2 !='\0'; ++s1, ++s2)
		if (*s1 != *s2)
			return (*s1 - *s2);
	if (*s1 != '\0')
		return (*s1);
	else if (*s2 != '\0')
		return (*s2);

	return (0);
}
