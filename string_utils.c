#include "main.h"

/**
 * _strdup - creates a copy of str in new memory location
 * @str: the string to be copied
 *
 * Return: NULL on failure, otherwise returns pointer to new string
 */
char *_strdup(char *str)
{
	char *ptr, *new;
	int length = 0, n;

	if (str == NULL)
		return (NULL);

	ptr = str;
	while (*ptr)
	{
		ptr++;
		length++;
	}
	new = (char *) malloc(sizeof(char) * (length + 1));

	if (new == NULL)
		return (NULL);

	for (n = 0; n < length; n++)
		*(new + n) = *(str + n);
	*(new + n) = '\0';

	return (new);
}

/**
 * str_concat - concatenates two string in new memory
 * @s1: first string to be concatenated
 * @s2: second(following) string to be concatenated
 *
 * Return: returns NULL on failure otherwise returns pointer
 * to concatenated string
 */
char *str_concat(char *s1, char *s2)
{
	int len_s1, len_s2, n;
	char *ptr;

	if (s1 != NULL)
	{
		ptr = s1;
		len_s1 = 0;
		while (*ptr)
		{
			len_s1++;
			ptr++;
		}
	} else
		len_s1 = 0;

	if (s2 != NULL)
	{
		ptr = s2;
		len_s2 = 0;
		while (*ptr)
		{
			len_s2++;
			ptr++;
		}
	} else
		len_s2 = 0;
	ptr = (char *) malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (ptr == NULL)
		return (NULL);
	for (n = 0; n < len_s1; n++)
		*(ptr + n) = *(s1 + n);
	for (n = 0; n < len_s2; n++)
		*(ptr + len_s1 + n) = *(s2 + n);
	*(ptr + len_s1 + len_s2) = '\0';
	return (ptr);
}

/**
 * _strlen - returns the lenght of the string
 * @s: string whose length needs to be determined
 *
 * Return: returns an int which is the length of the string pointed to by s
 */
int _strlen(const char *s)
{
	int count = 0;

	while (*s)
	{
		count++;
		s++;
	}
	return (count);
}

/**
 * _strcmp - lexographically compares s1 and s2
 * @s1: first string to be compared
 * @s2: second string to be compared
 *
 * Return: negative if s1 less than s2 , positive if s1 greater than s2 and
 * 0 if strings are equal
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 - *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strstr - returns the location of a substring in a string
 * @haystack: the string to be searched
 * @needle: the substring to searhc
 *
 * Return: pointer to the start of the substring or NULL
 */
char *_strstr(char *haystack, const char *needle)
{
	while (*haystack)
	{
		const char *ptr = needle, *start = haystack;

		while (*start && *ptr)
		{
			if (*start != *ptr)
				break;
			start++;
			ptr++;
		}
		if (!*ptr)
			return (haystack);
		haystack++;
	}
	return (0);
}
