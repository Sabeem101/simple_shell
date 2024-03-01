#include "shell.h"

/**
 * str_leng - returns the length of a string
 * @s: string
 *
 * Return: length of string
 */
int str_leng(char *s)
{
	int x = 0;

	if (!s)
	{
		return (0);
	}
	while (*s++)
		x++;
	return (x);
}
/**
 * _strcmp - compares two strings
 * @str1: first string
 * @str2: second string
 *
 * Return: negative if str1<str2, positive if str1>str2
 *		null if str1 == str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}
/**
 * _strcat - concatenates two strings
 * @dest: buffer destination
 * @src: buffer source
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *rtrn = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (rtrn);
}
/**
 * itstarts - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: pointer to next char of haystack or NULL
 */
char *itstarts(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return (NULL);
	}
	return ((char *)haystack);
}
