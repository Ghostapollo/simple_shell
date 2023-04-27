#ifndef _SHELL_H_
#define _SHELL_H_

#include <stddef.h>
#include <stdio.h>

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

void printprompt(void);
int isbuiltin(const char *cmd);
char **tokenize(char *input);
void executebuiltin(char **tokens);
int executecmd(const char *name, char *const argv[], char *const env[]);
void __exit(char **tokens, char **history, int fd);
void _env(char **tokens);
char *check_path(char *file);
int check_file(char *dirname, char *file);
char *_strdup(char *str);
int  _strlen(char *str);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *s1, char *s2);
char *_strtok(char *str, char *delim);
int isdelim(char ch, char *delim);
int _atoi(char *str);
void sighandler(int sig_n);
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
ssize_t _getline(char **lineptr, size_t *n, int fd);
void printhistory(char **history);
void help(char **tokens);
void updatehistory(char **history, int fd);

#endif /* _SHELL_H_ */
