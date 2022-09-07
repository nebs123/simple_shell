#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "main.h"

/**
 * str_split - splits string into tokens and returns array of tokens
 * @str: string to be split
 * Return: an array of string tokens
 */
char **str_split(char *str)
{
	unsigned int arr_size = 10, next = 0;
	char **arr, *ptr;

	arr = malloc(sizeof(*arr) * arr_size);
	if (!arr)
		return (NULL);
	ptr = strtok(str, " ");
	if (ptr)
	{
		arr[next] = ptr;
		next++;
	}
	while ((ptr = strtok(NULL, " ")))
	{
		if (arr_size == next)
		{
			arr = copier(arr, &arr_size, 10, next);
			if (!arr)
				return (NULL);
		}
		arr[next] = ptr;
		next++;
	}
	if (arr_size == next)
	{
		arr = copier(arr, &arr_size, 1, next);
		if (!arr)
			return (NULL);
	}
	arr[next] = NULL;
	return (arr);
}

/**
 * copier - manages copying array when there is about to be overflow
 * @arr: array to be copied
 * @arr_size: pointer to integer holding the array size
 * @increment: the number by which array is to be expanded
 * @next: the position the next element is to be placed/ also no of elements on
 * array
 * Return: returns pointer to the new array
 */
char **copier(char **arr, unsigned int *arr_size, unsigned int increment,
	      unsigned int next)
{
	char **temp = malloc(sizeof(*arr) * (*arr_size + increment));

	if (!temp)
	{
		free(arr);
		return (NULL);
	}
	*arr_size = *arr_size + increment;
	copy_arr(arr, temp, next);
	free(arr);
	return (temp);
}
/**
 * copy_arr - copies string array of size len from origin to dest
 * @origin: origin string array
 * @dest: destination string array
 * @len: length of data to be copied
 * Return: void (no return)
 */
void copy_arr(char **origin, char **dest, unsigned int len)
{
	unsigned int x;

	if (origin == NULL || dest == NULL)
		return;
	for (x = 0; x < len; x++)
	{
		dest[x] = origin[x];
	}
}

/**
 * str_split2 - splits string into tokens and returns array of tokens
 * @str: string to be split
 * Return: an array of string tokens
 */
char **str_split2(char *str)
{
	unsigned int arr_size = 10, next = 0;
	char **arr, *tok_start = NULL;

	arr = malloc(sizeof(*arr) * arr_size);
	if (!arr)
		return (NULL);
	while (*str)
	{
		if (*str != ' ' && tok_start == NULL)
			tok_start = str;
		if (tok_start && *str == ' ')
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
