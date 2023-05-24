#include"shell.h"

/**
 * _environ - prints the environ
 * @env: character
 * Return: environ
 */
void print_env(char **env)
{
	env = environ;
	while (*env != NULL)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}
