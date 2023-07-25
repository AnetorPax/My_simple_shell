#include "simple_shell.h"

/**
 * _getline - reads a line from standard input
 *
 * Return: Pointer to the line read. Otherwise NULL
 */
char *_getline(void)
{
	static char buffer[READ_SIZE];
	static int pos;
	static int bytes_read;
	char *line = NULL;
	int line_len = 0;

	while (1)
	{
		if (pos >= bytes_read)
		{
			bytes_read = read(STDIN_FILENO, buffer, READ_SIZE);
			if (bytes_read <= 0)
				break;
			pos = 0;
		}
		while (pos < bytes_read && buffer[pos] != '\n')
		{
			line = realloc(line, line_len + 2);
			if (!line)
			{
				perror("realloc error");
				exit(EXIT_FAILURE);
			}
			line[line_len++] = buffer[pos++];
		}
		if (pos < bytes_read && buffer[pos] == '\n')
		{
			line = realloc(line, line_len + 2);
			if (!line)
			{
				perror("realloc error");
				exit(EXIT_FAILURE);
			}
			line[line_len++] = buffer[pos];
			line[line_len] = '\0';
			return (line);
		}
	}
	free(line);
	return (NULL);
}
