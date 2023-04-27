#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "execute.h"
#include <sys/types.h>
#include <sys/wait.h>

int execute(char **args)
{
	pid_t pid;
	int status;
	pid = fork();

	if (pid == 0)
	{
		/* Child process */
		if (execvp(args[0], args) == -1)
		{
			perror("execute");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		/* Fork error */
		perror("execute");
	}
	else
	{
		/* Parent process */
		do
		{
			waitpid(pid, &status, WUNTRACED);
		}

		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}
