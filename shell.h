#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>


/**
 * struct process_builtin - structure to hold a command and a
 * function pointer to hold the command
 *
 * @cmd: the command to execute
 * @execute_builtin: pointer to a function that takes a command and
 * executes it
 *
 */
struct process_builtin
{
	char *cmd;
	void (*execute_builtin)(char **tokens);
};
typedef struct process_builtin builtin_t;

extern char **environ;

int _putchar(char c);
int access(const char *pathname, int mode);
int chdir(const char *path);
int close(int fd);
int closedir(DIR *dirp);
int execve(const char *pathname, char *const argv[], char *const envp[]);
void exit(int status);
void _exit(int status);
int fflush(FILE *stream);
pid_t fork(void);
void free(void *ptr);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
pid_t getpid(void);
int isatty(int fd);
int kill(pid_t pid, int sig);
DIR *opendir(const char *name);
void perror(const char *s);
ssize_t read(int fd, void *buf, size_t count);
struct dirent *readdir(DIR *dirp);
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
int stat(const char *pathname, struct stat *statbuf);
int fstat(int fd, struct stat *statbuf);
int lstat(const char *pathname, struct stat *statbuf);
char *strtok(char *str, const char *delim);
pid_t wait(int *wstatus);
pid_t waitpid(pid_t pid, int *wstatus, int options);
pid_t wait3(int *wstatus, int options, struct rusage *rusage);
pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);
ssize_t write(int fd, const void *buf, size_t count);
void prompt(void);
void change_directory(char **tokens);

#endif
