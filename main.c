#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT 1024

/**
 * main - Entry point for the simple shell program
 *
 * Return: Always 0 on successful completion
*/
int main(void)
{
	char input[MAX_INPUT];

	while (1)
	{
		printf("simple_shell$ ");
		if (!fgets(input, MAX_INPUT, stdin))
		{
			printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		pid_t pid = fork();

		if (pid < 0)
		{
			perror("fork error");
			exit(1);
		}
		else if (pid == 0)
		{
			if (execlp(input, input, (char *)NULL) == -1)
			{
				perror("exec error");
				exit(1);
			}
			else
			{
				int status;
				if (waitpid(pid, &status, 0) == -1)
			{
				perror("waitpid error");
				exit(1);
			}
			}
		}
	}
	return (0);
}

void prompt(void);
void execute_command(char *command);

int main(void)
{
	while (1)
	{
		prompt();
		char input[100];

		fgets(input, sizeof(input), stdin);
		input[strlen(input) - 1] = '\0';
		execute_command(input);
	}
	return (0);
}
