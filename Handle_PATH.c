#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/times.h>
/**
 * find_command - searches for the command in the PATH and updates args
 * @args: pointer to an array of Arguments located
 *
 * Return: 1 if command found, 0 if not found
 */
int find_command(char *args[])
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");
	char *full_path = NULL;
	int found = 0;

	if (args[0][0] == '/')
	{
		if (access(args[0], X_OK) == 0)
			return (1);
		return (0);
	}

	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(args[0]) + 2);
		if (full_path != NULL)
		{
			sprintf(full_path, "%s/%s", dir, args[0]);
			if (access(full_path, X_OK) == 0)
			{
				args[0] = full_path;
				found = 1;
				break;
			}
			free(full_path);
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (found);
}
