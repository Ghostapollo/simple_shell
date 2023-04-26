#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

#define MAX_ALIASES 100
#define MAX_ALIAS_NAME_LENGTH 50
#define MAX_ALIAS_VALUE_LENGTH 100

struct alias
{
	char name[MAX_ALIAS_NAME_LENGTH];
	char value[MAX_ALIAS_VALUE_LENGTH];
};

struct alias aliases[MAX_ALIASES];
int num_aliases = 0;

void print_alias(struct alias *alias)
{
	char *buf;
	vsprintf(&buf, "%s='%s'\n", alias->name, alias->value);
	write(STDOUT_FILENO, buf, strlen(buf));
	free(buf);
}

void print_aliases(void)
{
	for (int i = 0; i < num_aliases; i++)
	{
		print_alias(&aliases[i]);
	}
}

struct alias *find_alias(char *name)
{
	for (int i = 0; i < num_aliases; i++)
	{
		if (strcmp(aliases[i].name, name) == 0)
		{
			return (&aliases[i]);
		}
	}
	return (NULL);
}

void add_alias(char *name, char *value)
{
	struct alias *existing_alias = find_alias(name);
	if (existing_alias != NULL)
	{
		strcpy(existing_alias->value, value);
	}
	else
	{
		if (num_aliases >= MAX_ALIASES)
		{
			char *error_msg;
			asprintf(&error_msg, "alias: too many aliases defined\n");
			write(STDERR_FILENO, error_msg, strlen(error_msg));
			free(error_msg);
			exit(EXIT_FAILURE);
		}
		struct alias new_alias;
		strcpy(new_alias.name, name);
		strcpy(new_alias.value, value);
		aliases[num_aliases++] = new_alias;
	}
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		print_aliases();
		exit(EXIT_SUCCESS);
	}
	if (strcmp(argv[1], "-p") == 0)
	{
		if (argc == 2)
		{
			print_aliases();
			exit(EXIT_SUCCESS);
		}
		else
		{
			for (int i = 2; i < argc; i++)
			{
				struct alias *alias = find_alias(argv[i]);
				if (alias != NULL)
				{
					print_alias(alias);
				}
				else
				{
					char *error_msg;
					asprintf(&error_msg, "alias: %s: not found\n", argv[i]);
					write(STDERR_FILENO, error_msg, strlen(error_msg));
					free(error_msg);
					exit(EXIT_FAILURE);
				}
			}
			exit(EXIT_SUCCESS);
		}
	}
	for (int i = 1; i < argc; i++)
	{
		char *equals = strchr(argv[i], '=');
		if (equals != NULL)
		{
			*equals = '\0';
			add_alias(argv[i], equals + 1);
		}
		else
		{
			struct alias *alias = find_alias(argv[i]);
			if (alias != NULL)
			{
				print_alias(alias);
			}
			else
			{
				char *error_msg;
				asprintf(&error_msg, "alias: %s: not found\n", argv[i]);
				write(STDERR_FILENO, error_msg, strlen(error_msg));
				free(error_msg);
				exit(EXIT_FAILURE);
			}
		}
	}
	exit(EXIT_SUCCESS);
}
