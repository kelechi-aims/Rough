#include "shell.h"

#define BUFFER_SIZE 4096
#define INITIAL_LINE_SIZE 128

/**
 * _read_buffer - reads user input
 * @stream: file to read from
 * @buffer: to store bytes read
 * @size: size of buffer
 * Return: bytes read
 */
ssize_t _read_buffer(FILE *stream, char *buffer, size_t size)
{
	static size_t bytesRead;

	bytesRead = read(fileno(stream), buffer, size);
	return (bytesRead);
}

/**
 * _expand_line - increase the line buffer size when needed
 * @lineptr: a double pointer to user input
 * @n: initial line size
 * Return: zero on success
 */
ssize_t _expand_line(char **lineptr, ssize_t *n)
{
	char *newLine;
	
	*n += INITIAL_LINE_SIZE;
	newLine = realloc(*lineptr, *n);
	if (newLine == NULL)
	{
		free(*lineptr);
		return (-1);
	}
	*lineptr = newLine;
	return (0);
}

/**
 * _append_character - appends a character to the line
 * @buffer and expands it if necessary.
 * @lineptr: a double pointer to user input
 * @totalBytesRead: total Bytes Read
 * @c: charater
 * Return: void
 */
void _append_character(char **lineptr, ssize_t *totalBytesRead, char c)
{
	ssize_t *n = 0;

	(*lineptr)[(*totalBytesRead)++] = c;
	if (*totalBytesRead + 1 >= *n)
	{
		_expand_line(lineptr, n);
	}
}

/**
 * _getline - use a buffer to read many chars at once
 * @lineptr: a double to the buffer
 * @n: a pointer to the size of lineptr
 * @stream: a pointer to where the characters are read from
 * Return: the number of characer read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[BUFFER_SIZE];
	size_t bufferPos = 0;
	size_t bytesRead = 0;
	size_t lineSize = 0;
	ssize_t totalBytesRead = 0;
	char *line = NULL;
	char c;

	if (lineptr == NULL || n == NULL || stream == NULL)
	{
		return (-1);
	}
	while (1)
	{
		if (bufferPos >= bytesRead)
		{
			bytesRead = _read_buffer(stream, buffer, BUFFER_SIZE);
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
		while (bufferPos < bytesRead)
		{
			c = buffer[bufferPos++];
			_append_character(&line, &totalBytesRead, c);
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
