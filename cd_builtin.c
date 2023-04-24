#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "main.h"

#define MAX_PATH_LEN 1024

/**
 * Changes the current directory of the process.
 *
 * @param: path The directory to change to.
 *
 * @return: 0 on success, -1 on failure.
 */
int cd_builtin(char *path)
{
	char old_path[MAX_PATH_LEN];
	if (getcwd(old_path, MAX_PATH_LEN) == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	
	if (path == NULL)
	{
		path = getenv("HOME");
	}
	else if (strcmp(path, "-") == 0)
	{
		path = getenv("OLDPWD");
		write(STDOUT_FILENO, path, strlen(path));
		write(STDOUT_FILENO, "\n", 1);
	}
	if (chdir(path) != 0)
	{
		perror("chdir");
		return (-1);
	}
	
	char new_path[MAX_PATH_LEN];
	if (getcwd(new_path, MAX_PATH_LEN) == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	
	setenv("OLDPWD", old_path, 1);
	setenv("PWD", new_path, 1);
	return (0);
}
