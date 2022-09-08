#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - runs the main loop of the shell
 * @ac: no of command line arguments
 * @av: array of str which correspond to command line args
 * @env: array of str which correspond to environment vars
 * Return: returns 0 on success otherwise -1
 */
int main(int ac, char **av, char **env)
{
	char *buf = NULL, **split = NULL, *path = NULL;
	size_t num = 0;
	ssize_t num2 = 0;
	int done = 1, status, count, exit_st = 0;

	(void) ac;
	for (count = 1; done; count++)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "($) ", _strlen("(S) "));
			fflush(stdout);
		}
		num2 = getline(&buf, &num, stdin);
		if (num2 == -1)
			done = 0;
		else
		{
			if (buf[num2 - 1] == '\n')
				buf[num2 - 1] = '\0';
			split = str_split2(buf);
			if (*split == NULL)
			{
				free_mem(&buf, &num, &split, &path);
				continue;
			}
			if (builtin(split, buf, path, exit_st))
			{
				path = get_path(split[0], &status);
				if (path)
					exit_st = command(path, split, env);
				else
					exit_st = perr(av[0], count, split[0], status);
			}
		}
		free_mem(&buf, &num, &split, &path);
	}
	return (exit_st);
}

/**
 * command - executes program specified by path with args split and environment
 * @path: full name of the program to be executed
 * @split: array of strings which are the command line arguments specified
 * @env: environment of the process executing the program
 * Return: void( no return)
 */
int command(char *path, char **split, char **env)
{
	pid_t child;
	int status;

	child = fork();
	if (child == -1)
	{
		perror("Error");
		_exit(-1);
	} else if (child == 0)
	{
		if (execve(path, split, env) == -1)
		{
			perror("Error");
			_exit(-1);
		}
	} else
	{
		if (wait(&status) == -1)
		{
			perror("Error");
			_exit(-1);
		}
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

/**
 * free_mem - frees the memory held by the variables inputted
 * @buf: pointer to buffer for holding the line input
 * @num: size of buffer
 * @split: pointer to array of tokens found in buf
 * @path: pointer to arrray of full path of the program
 * Return: void (no return)
 */
void free_mem(char **buf, size_t *num, char ***split, char **path)
{
	if (buf)
	{
		free(*buf);
		*buf = NULL;
		*num = 0;
	}
	if (split)
	{
		free(*split);
		*split = NULL;
	}
	if (path)
	{
		free(*path);
		*path = NULL;
	}
}

/**
 * perr - prints out the error for the command line
 * @prog: name/path of program being executed
 * @count: the line number count
 * @cmd: string which is the command/program executed
 * @stat: status of the error
 * Return: void (no return)
 */
int perr(char *prog, int count, char *cmd, int stat)
{
	int ret;

	if (stat == -1)
	{
		write(STDOUT_FILENO, prog, _strlen(prog));
		write(STDOUT_FILENO, ": ", _strlen(": "));
		write_int(count);
		write(STDOUT_FILENO, ": ", _strlen(": "));
		write(STDOUT_FILENO, cmd, _strlen(cmd));
		write(STDOUT_FILENO, ": ", _strlen(": "));
		write(STDOUT_FILENO, "Permission denied\n",
		      _strlen("Permission denied\n"));
		ret = 126;
	} else
	{
		write(STDOUT_FILENO, prog, _strlen(prog));
		write(STDOUT_FILENO, ": ", _strlen(": "));
		write_int(count);
		write(STDOUT_FILENO, ": ", _strlen(": "));
		write(STDOUT_FILENO, cmd, _strlen(cmd));
		write(STDOUT_FILENO, ": ", _strlen(": "));
		write(STDOUT_FILENO, "not found\n", _strlen("not found\n"));
		ret = 127;
	}
	fflush(stdout);
	return (ret);

}

/**
 * builtin - executes the builting shell command
 * @args: command line arguments
 * @buf: buffer that holds string of line
 * @path: path returned by get_path
 * @exit_st: exit status of the previous command
 * Return: status code which designates whether builitin was executed
 */
int builtin(char **args, char *buf, char *path, int exit_st)
{
	if (_strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(buf);
		free(path);
		_exit(exit_st);
	} else if (_strcmp(args[0], "env") == 0)
	{
		printenv();
		return (0);
	} else
		return (-1);
}
