#include "shell.h"

/**
 * shell_loop - performs the loop operation
 * @av: argument vector
 * @env: environment parament
 * Return: void
 */
void shell_loop(char **av, char **env)
{
	char *command = NULL;
	size_t command_length = 0;

	while (1)
	{
		prompt();
		fflush(stdout);
		if (getline(&command, &command_length, stdin) == -1)
		{
			free(command);
			exit(0);
		}
		command[strcspn(command, "\n")] = '\0';
		av = _tokenize(command, " ");
		if (av == NULL)
		{
			perror("Tokenization error");
			continue;
		}
		process_command(command, av, env);
	}
}

/**
 * main - entry point of the shell
 * @ac: argument counter
 * @av: argument vector
 * @env: environment parameter
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	char *command;

	if (ac > 1)
	{
		command = av[1];
		if (execve(command, av, env) == -1)
		{
			perror(av[0]);
			exit(1);
		}
	}
	else
	{
		shell_loop(av, env);
	}
	return (0);
}
