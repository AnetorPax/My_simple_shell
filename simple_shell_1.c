#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define _GNU_SOURCE

/**
 * main - the beginning of the program
 * Return: 0 Always Success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *prompt = "#cisfun$ ";
	int status;
	pid_t pid;
	char *const argv[] = {line, NULL};

	while (1)
	{
		printf("%s", prompt);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				putchar('\n');
			break;
		}

		line[read - 1] = '\0';

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execve(line, argv, NULL) == -1)
			{
				perror("execve error");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (wait(&status) == -1)
			{
				perror("wait");
				exit(EXIT_FAILURE);
			}
		}
	}

	free(line);

	return(0);
}
