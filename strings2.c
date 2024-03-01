#include "shell.h"

/**
 * cpy_str - copies a string
 * @dest: destination
 * @src: source
 * @a: amount of characters copied
 *
 * Return: concatenated string
 */
char *cpy_str(char *dest, char *src, int a)
{
	int y, x = 0;
	char *z = dest;

	while (src[x] != '\0' && x < a - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < a)
	{
		y = x;
		while (y < a)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (z);
}
/**
 * cat_str - concatenates two strings
 * @dest: destination
 * @src: source
 * @a: amount of bytes to be used
 *
 * Return: concatenated string
 */
char *cat_str(char *dest, char *src, int a)
{
	int x = 0, y = 0;
	char *z = dest;

	while (dest[x] != '\0')
		x++;
	while (src[y] != '\0' && y < a)
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	if (y < a)
		dest[x] = '\0';
	return (z);
}
/**
 * str_char - locates a character in a string
 * @str: string tp be parsed
 * @c: character to find
 *
 * Return: pointer to the character
 */
char *str_char(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
