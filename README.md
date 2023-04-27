0x16. C - Simple Shell

This project is based on a simple UNIX command interpreter that was built as a part of ALX software engineering project
The project contains a main.c, main .h and all the prototypes and header files used in this project.

man or help:

sh (Run sh as well);

Unless specified otherwise, your program must have the exact same output as sh (/bin/sh) as well as the exact same error output.
The only difference is when you print an error, the name of the program must be equivalent to your argv[0] (See below)
Example of error with sh:

$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
Same error with your program hsh:

$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$


List of allowed functions and system calls

access (man 2 access), chdir (man 2 chdir), close (man 2 close), closedir (man 3 closedir), execve (man 2 execve), exit (man 3 exit),
_exit (man 2 _exit), fflush (man 3 fflush), fork (man 2 fork), free (man 3 free), getcwd (man 3 getcwd), getline (man 3 getline),
getpid (man 2 getpid), isatty (man 3 isatty), kill (man 2 kill), malloc (man 3 malloc), open (man 2 open), opendir (man 3 opendir),
perror (man 3 perror), read (man 2 read), readdir (man 3 readdir), signal (man 2 signal), stat (__xstat) (man 2 stat), lstat (__lxstat) (man 2 lstat), fstat (__fxstat) (man 2 fstat), strtok (man 3 strtok), wait (man 2 wait), waitpid (man 2 waitpid), wait3 (man 2 wait3),
wait4 (man 2 wait4), write (man 2 write).



Compilation

The shell project was complied using: gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh



Testing

The shell project was instructed to work like this in interactive mode:
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
But also in non-interactive mode:

$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$

Tasks

0. Write a beautiful code that passes the Betty checks

1. Write a UNIX command line interpreter.

Usage: simple_shell
Our Shell should:

Display a prompt and wait for the user to type a command. A command line always ends with a new line.
The prompt is displayed again each time a command has been executed.
The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
The command lines are made only of one word. No arguments will be passed to programs.
If an executable cannot be found, print an error message and display the prompt again.
Handle errors.
You have to handle the “end of file” condition (Ctrl+D)
You don’t have to:

use the PATH
implement built-ins
handle special characters : ", ', `, \, *, &, #
be able to move the cursor
handle commands with arguments
execve will be the core part of your Shell, don’t forget to pass the environ to it…

2. Handle command lines with arguments

3. Handle the PATH: fork must not be called if the command doesn’t exist

4. Implement the exit built-in, that exits the shell
Usage: exit
You don’t have to handle any argument to the built-in exit

5. Implement the env built-in, that prints the current environment

6. Write your own getline function
Use a buffer to read many chars at once and call the least possible the read system call
You will need to use static variables
You are not allowed to use getline
You don’t have to: be able to move the cursor

The rest of the tasks where advanced tasks.
