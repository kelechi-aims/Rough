#include "shell.h"

/**
 * execute_command - executes single commands
 * @command: a pointer to the command
 * @av: a double pointer to the argument vectors
 * @env: a double pointer to the env variable
 * Return: void
 */

void execute_command(char *command, char **av, char **env)
{
	int status;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/*if (execve(command, av, NULL) == -1) before env implement*/
		if (execve(command, av, env) == -1)
		{
			perror("Execve");
			free(command);
			exit(EXIT_FAILURE);
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

/**
 * process_command - executes multiple commands
 * @input: double pointer to command
 * @av: double pointer to argument vector
 * @env: double pointer to env
 * Return: void
 */
void process_command(char *command, char **av, char **env)
{
	char *command_path;

	/**
	 * char **tokens = _tokenize(input, ";");
	*int i = 0;
	*char **av;
	*while (tokens[i] != NULL)
	*{
	*	av = _tokenize(tokens[i], " \t\r\a\n");
	*/
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
			print_env(env);
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
			execute_command(command_path, av, env);
			cleaner(av);
			cleanup(command_path, av);
		}
	}
}

/**
 * if (_strcmp(av[0], "setenv") == 0)
*	{
*				_setenv(av);
*			}
*			if (_strcmp(av[0], "unserenv") == 0)
*			{
*				_unsetenv(av);
*			}
*			if (_strcmp(av[0], "cd") == 0)
*			{
*				_cd(av);
*			}
*			else
*			{
*				executor(av, env);
*			}
*		}
*		free(av);
*		i++;
*	}
*	free(tokens);
*}
*/
