#include "shell.h"

/**
 * handle_interrupt - handles Ctrl+C
 * @signum: integer
 * Return: void
 */
void handle_interrupt(int signum)
{
	(void)signum;

}
/**
 * exe_cmd1 - executes command
 * @command: command to execute
 * @av: argument vector
 * @env: enviroment parameter
 * Return: void
 */
void exe_cmd1(char *command, char **av)
{
	char *command_path;

	if (av[0] != NULL)
	{
		if (strcmp(av[0], "exit") == 0)
		{
			handle_exit(command, av);
		}
		else if (strcmp(av[0], "env") == 0)
		{
			cleaner(av);
			cleanup(NULL, av);
			print_env(environ);
		}
		else
		{
			command_path = find_command(av[0]);
			if (command_path == NULL)
			{
				perror(av[0]);
				cleaner(av);
				cleanup(NULL, av);
				return;
			}
			executor(command_path, av);
			cleaner(av);
			cleanup(NULL, av);
		}
	}
/*	free(command_path);*/
}
/**
 * shell_loop - performs the loop operation
 * @av: argument vector
 * Return: void
 */
void shell_loop(char **av)
{
	char *command = NULL;
	/*size_t command_length = 0;*/

	/*signal(SIGINT, handle_interrupt);*/

	while (1)
	{
		prompt();
		fflush(stdout);
		command = read_cmd();
		command[strcspn(command, "\n")] = '\0';
		if (strlen(command) == 0 || strspn(command, " \t") == strlen(command))
		{
			/*return;*/
			continue;
		}
		av = _tokenize(command, " \t");
		if (av == NULL)
		{
			perror("Tokenization error");
			cleanup(command, av);
			return;
		}

		exe_cmd1(command, av);
		free(command);
		command = NULL;
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
	if (ac > 1)
	{
		exe_cmd1(av[1], av);
		return (0);
	}
	else
	{
		shell_loop(av);
	}
	return (0);
}
