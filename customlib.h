#include <stddef.h>
#include "shell.h"

int _strcmp(const char *s1, const char *s2);

int my_strcmp(const char *s1, const char *s2)
{
	if (s1 == NULL || s2 == NULL)
	{
		return -1;  // or some other error code
	}
	else
	{
		return _strcmp(s1, s2);
	}
}
