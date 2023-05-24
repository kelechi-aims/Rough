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
	int status;
	pid_t pid;

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

		pid = fork();
		if (pid < 0)
		{
			perror("Fork");
			exit(1);
		}
		else if (pid == 0)
		{
			if (execve(command, av, NULL) == -1)
			{
				perror(av[0]);
				exit(1);
			}
		}
		else
		{
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("waitpid");
				exit(1);
			}
		}
	}
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
