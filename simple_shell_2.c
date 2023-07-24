#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/times.h>

/**
 * exec_command - executes the command parsed to the shell
 * @args: pointer to the command parsed to shell
 *
 * Return: Nothing
 */
void exec_command(char *args[])
{
	if (execve(args[0], args, NULL) == -1)
	{
		perror("execve error");
		exit(EXIT_FAILURE);
	}
}


/**
 * parse_args - breaks string and locates commands from arguments
 * @str: pointer to the string to be examined
 * @args: pointer to an array of Arguments located
 * Return: Nothing
 */
void parse_args(char *str, char *args[])
{
	char *token;
	int i = 0;

	token = strtok(str, " ");
	while (token)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}

/**
 * main - creates a shell that executes commands with arguements
 *
 * Return: 0 if Successful and -1 if otherwise
 */
int main(void)
{
	char *input = NULL;
	size_t in_size = 0;
	char *args[1024];
	int status;
	ssize_t in_read;
	pid_t pid;

	while (1)
	{
		printf("#cisfun$ ");
		in_read = getline(&input, &in_size, stdin);
		if (in_read == -1)
			break;

		if (input[in_read - 1] == '\n')
			input[in_read - 1] = '\0';

		parse_args(input, args);

		pid = fork();
		if (pid == -1)
			perror("fork error");
		else if (pid == 0)
			exec_command(args);
		else
			wait(&status);
	}
	free(input);
	printf("\n");
	return (0);
}
