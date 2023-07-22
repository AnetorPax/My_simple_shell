#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

/**
 * list_directory_contents - Locates the contents of a directory
 * @dir_path: PATH to locate the directory
 * Return: Nothing
 */
void list_directory_contents(const char *dir_path)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir(dir_path);
	if (dir == NULL)
	{
		perror("opendir");
		return;
	}

	while ((entry = readdir(dir)) != NULL)
	{
		printf("%s\n", entry->d_name);
	}

	closedir(dir);
}

/**
 * display_file_content - display the content of a file.
 * @file_path: points to the PATH the file is located
 * Return: Nothing
 */
void display_file_content(const char *file_path)
{
	FILE *file;
	char buffer[1024];
	size_t bytes_read;

	file = fopen(file_path, "r");
	if (file == NULL)
	{
		perror("fopen");
		return;
	}

	while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0)
	{
		fwrite(buffer, 1, bytes_read, stdout);
	}

	fclose(file);
}
