#include "simple_shell.h"

/**
 * _getline - reads a line from standard input
 *
 * Return: Pointer to the line read. Otherwise NULL
 */
char *_getline(void)
{
	static char buffer[READ_SIZE];
	static ssize_t pos = 0;
	ssize_t bytes_read = 0, i = 0;
	char *line = NULL;

	while (1)
	{
		if (pos >= bytes_read)
		{
			bytes_read = read(STDIN_FILENO, buffer, READ_SIZE);
			if (bytes_read <= 0)
				return (NULL);
			if (bytes_read == -1)
				return (NULL);
			pos = 0;
		}
		if (buffer[pos] == '\n')
		{
			buffer[pos] = '\0';
			line = malloc(pos + 1);
			if (line == NULL)
				return (NULL);
			for (i = 0; i < pos; i++)
				line[i] = buffer[i];
			line[i] = '\0';
			pos++;
			return (line);
		}
		pos++;
	}
}
/**
 * clean_up - clean up memory allocated to avoid memory leaks
 * @char: pointer to the variable to clean
 * Return: Nothing
 */
void clean_up(char *line)
{
	if (line)
		free(line);
}
