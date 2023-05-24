#include "shell.h"

/**
 * shell_loop - performs the loop operation
 * @av: argument vector
 * Return: void
 */
void shell_loop(char **av)
{
	char *command = NULL;
	size_t command_length = 0;
	char *command_path, *command_copy;

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
			cleanup(command, av);
			continue;
		}
		if (av[0] != NULL && strcmp(av[0], "exit") == 0)
		{
			cleaner(av);
			cleanup(command, av);
			exit(0);
		}
		else
		{
			command_path = find_command(av[0]);
			if (command_path == NULL)
			{
				cleaner(av);
				cleanup(command, av);
				exit(1);
			}
			command_copy = strdup(command_path);
			execute_command(command_copy, av);
			cleaner(av);
			free(command_copy);
		}
		cleanup(command_path, av);
	}
	/*cleaner(av);*/
	cleanup(command_path, av);
}
/**
 * main - entry point of the shell
 * @ac: argument counter
 * @av: argument vector
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	char *command;

	if (ac > 1)
	{
		command = av[1];
		if (execve(command, av, NULL) == -1)
		{
			perror(av[0]);
			exit(1);
		}
	}
	else
	{
		shell_loop(av);
	}
	return (0);
}
