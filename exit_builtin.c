#include "main.h"

/**
 * exit_shell - exits the shell
 */
void exit_shell(void)
{
	exit(EXIT_SUCCESS);
}

/**
 * main - the entry point of the program
 * Return: Always 0
 */
int main(void)
{
	char *input;
	char *args[100];
	int num_args;
	int status;
	
	do
	{
		prompt();
		
		input = read_input();
		num_args = parse_input(input, args);
		
		if (num_args > 0)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				free(input);
				exit_shell();
			}
			else if (strcmp(args[0], "env") == 0)
			{
				char **environ_copy = NULL;
				int i, num_environ_vars = 0;
			}	
				for (i = 0; environ[i] != NULL; i++)
					num_environ_vars++;
				
				environ_copy = malloc(sizeof(char *) * (num_environ_vars + 1));
				
				for (i = 0; environ[i] != NULL; i++)
					environ_copy[i] = strdup(environ[i]);
				
				environ_copy[i] = NULL;
				
				for (i = 0; environ_copy[i] != NULL; i++)
					write(STDOUT_FILENO, environ_copy[i], strlen(environ_copy[i]));
				free(environ_copy);
		}
		else
		{
			if (check_command(args))
				execute_command(args);
			else
				write(STDERR_FILENO, "command not found\n", strlen("command not found\n"));
		}
	}
	free(input);
}
while (1);

return (0);
}
