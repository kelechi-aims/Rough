#include "shell.h"

/**
 * _getline - use a buffer to read many chars at once
 * @lineptr: a double to the buffer
 * @n: a pointer to the size of lineptr
 * @stream: a pointer to where the characters are read from
 * Return: the number of characer read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[4096];
	static size_t bufferPos;
	static size_t bytesRead;
	ssize_t totalBytesRead = 0;
	char *line = NULL, *newLine, c;
	ssize_t lineSize = 0;

	if (lineptr == NULL || n == NULL || stream == NULL)
	{
		return (-1);
	}
	while (1)
	{
		if (bufferPos >= bytesRead)
		{
			bytesRead = read(fileno(stream), buffer, sizeof(buffer));
			bufferPos = 0;
			if (bytesRead <= 0)
			{
				if (totalBytesRead == 0)
				{
					return (-1);
				}
				else
				{
					break;
				}
			}
		}
		if (lineSize < totalBytesRead + 1)
		{
			lineSize += 128;
			newLine = realloc(line, lineSize);
			if (newLine == NULL)
			{
				free(line);
				return (-1);
			}
			line = newLine;
		}
		while (bufferPos < bytesRead)
		{
			c = buffer[bufferPos++];
			line[totalBytesRead++] = c;
			if (c == '\n')
			{
				break;
			}
		}
		if (line[totalBytesRead - 1] == '\n')
		{
			break;
		}
	}
	line[totalBytesRead] = '\0';
	*lineptr = line;
	*n = lineSize;
	return (totalBytesRead);
}

/**
 * read_cmd - handles the getline
 * Return: read command
 */
char *read_cmd(void)
{
	size_t command_len = 0;
	ssize_t cmd = 0;
	char *command = NULL;

	cmd = getline(&command, &command_len, stdin);
	if (cmd == -1)
	{
		free(command);
		exit(0);
		command[strcspn(command, "\n")] = '\0';
	}
	return (command);
}
