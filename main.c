#include "main.h"

#define MAX_INPUT 1024
#define MAX_ARGS 64

// Function to parse the input string into an array of arguments
char **parse_input(char *input)
{
    // Allocate memory for the arguments array
    char **args = malloc(MAX_ARGS * sizeof(char *));
    if (!args)
    {
        perror("malloc error");
        exit(1);
    }

    // Use strtok to tokenize the input string by spaces and newlines
    char *arg = strtok(input, " \n");
    int i = 0;
    while (arg)
    {
        args[i++] = arg;
        arg = strtok(NULL, " \n");
    }
    // Set the final element of the array to NULL
    args[i] = NULL;

    // Return the array of arguments
    return args;
}

// Function to execute a single command with optional input/output redirection
void execute_command(char **args, int input_fd, int output_fd, int is_background)
{
    // Fork a new process to execute the command
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork error");
        exit(1);
    } else if (pid == 0)
    { // Child process
        // Redirect input and output as necessary
        if (input_fd != STDIN_FILENO)
	{
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != STDOUT_FILENO)
	{
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }
        // Execute the command using execvp
        if (execvp(args[0], args) == -1)
	{
            perror("execvp error");
            exit(1);
        }
        exit(0);
    } 
    else
    { // Parent process
        if (!is_background) {
            // Wait for the child process to finish, unless it is running in the background
            int status;
            do
	    {
                if (waitpid(pid, &status, WUNTRACED) == -1)
		{
                    perror("waitpid error");
                    exit(1);
                }
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }
}

// Function to execute a pipeline of commands
int execute_pipeline(char ***commands, int num_commands)
{
    // Keep track of the input file descriptor for each command in the pipeline
    int input_fd = STDIN_FILENO;
    // Loop over each command in the pipeline and execute it
    for (int i = 0; i < num_commands; i++)
    {
        // Keep track of the output file descriptor for the current command
        int output_fd = STDOUT_FILENO;
        // If this is the last command in the pipeline, and there are more commands after it, create a new pipe
        if (i == num_commands - 1 && commands[i + 1])
	{
            int fd[2];
            if (pipe(fd) == -1)
	    {
                perror("pipe error");
                exit(1);
            }
            // Set the output file descriptor for the current command to the write end of the pipe
            output_fd = fd[1];
            // Set the input file descriptor for the next command to the read end of the pipe
            input_fd = fd[0];
        }
        // Execute the current command with the appropriate input/output redirection and background status
        execute_command(commands[i], input_fd, output_fd)
    }
}
