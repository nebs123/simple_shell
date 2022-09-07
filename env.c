#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

/**
 * _getenv - fetch the value of an environment variable
 * @name: the name of the environment variable
 *
 * Return: string that contains the value for the env variable name
 */
char *_getenv(const char *name)
{
	int n;

	if (name == NULL)
		return (NULL);

	for (n = 0; environ[n]; n++)
	{
		if (_strstr(environ[n], name) == environ[n] &&
		   *(environ[n] + _strlen(name)) == '=')
		{
			return (environ[n] + _strlen(name) + 1);
		}
	}
	return (NULL);
}

/**
 * check_file - checks if the file exists and has execute permission
 * @file: the file to check for
 * @info: the pointer to hold status struct
 * @status: pointer to status that holds info about failed check
 * Return: returns pointer to the file if successful otherwise returns null
 */
char *check_file(char *file, struct stat *info, int *status)
{
	if (stat(file, info) == 0)
	{
		if (access(file, X_OK) == 0)
		{
			return (file);
		}
		else
		{
			*status = -1;
			return (NULL);
		}
	}
	else
		return (NULL);
}
/**
 * get_path - returns full path to program or executable if it exists
 * @file: name of command or executable
 * @status: pointer to status of failure
 * Return: pointer to full length of command or executable, null on failure
 */
char *get_path(char *file, int *status)
{
	char *s = _getenv("PATH"), *dup, **paths;
	struct stat info;
	int i;

	*status = 0;
	if (_strstr(file, "./") == file || _strstr(file, "../") == file
	    || _strstr(file, "/") == file)
	{
		if (check_file(file, &info, status))
			return (_strdup(check_file(file, &info, status)));
		else
			return (NULL);
	}
	dup = _strdup(s);
	if (dup == NULL)
		return (NULL);
	paths = str_delim(dup, ':');
	if (paths == NULL)
	{
		free(dup);
		return (NULL);
	}
	for (i = 0; paths[i]; i++)
	{
		char *p = str_concat(paths[i], "/"), *fp;

		fp = str_concat(p, file);
		free(p);
		if (check_file(fp, &info, status))
		{
			free(dup);
			free(paths);
			return (fp);
		}
		free(fp);
	}
	free(dup);
	free(paths);
	return (NULL);
}


/**
 * str_delim - splits string based on delimiter
 * @str: string to be split
 * @delim: character to split on
 * Return: array of split strings
 */
char **str_delim(char *str, char delim)
{
	unsigned int arr_size = 10, next = 0;
	char **arr, *tok_start = NULL;

	arr = malloc(sizeof(*arr) * arr_size);
	if (!arr)
		return (NULL);
	while (*str)
	{
		if (*str != delim && tok_start == NULL)
			tok_start = str;
		if (tok_start && *str == delim)
		{
			*str = '\0';
			if (arr_size == next)
			{
				arr = copier(arr, &arr_size, 10, next);
				if (!arr)
					return (NULL);
			}
			arr[next] = tok_start;
			next++;
			tok_start = NULL;
		}
		str++;
	}
	if (arr_size == next || (arr_size - 1) == next)
	{
		arr = copier(arr, &arr_size, 2, next);
		if (!arr)
			return (NULL);
	}
	if (tok_start)
	{
		arr[next] = tok_start;
		next++;
	}
	arr[next] = NULL;
	return (arr);
}

/**
 * printenv - prints the environment variables
 *
 * Return: void (no return)
 */
void printenv(void)
{
	int n;

	for (n = 0; environ[n]; n++)
	{
		write(STDOUT_FILENO, environ[n], _strlen(environ[n]));
		write(STDOUT_FILENO, "\n", _strlen("\n"));
	}
}
