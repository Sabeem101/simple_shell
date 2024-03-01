#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: destination
 * @src: source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
	{
		return (dest);
	}
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}
/**
 * _strdup - duplicates a string
 * @str: string to duplacate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int leng = 0;
	char *dup;

	if (str == NULL)
	{
		return (NULL);
	}
	while (*str++)
	{
		leng++;
	}
	dup = malloc(sizeof(char) * (leng + 1));
	if (!dup)
	{
		return (NULL);
	}
	for (leng++; leng--;)
		dup[leng] = *--str;
	return (dup);
}
/**
 * _putchar - writes the character c to stdout
 * @c: character to print
 *
 * Return: On success 1. on error -1 and errno is set appropriately.
 */
int _putchar(char c)
{
	static char buf[WRITE_BUFF];
	static int x;

	if (c == BUFF || x >= WRITE_BUFF)
	{
		write(1, buf, x);
		x = 0;
	}
	if (c != BUFF)
		buf[x++] = c;
	return (1);
}
/**
 * itputs - prints an input string
 * @str: the string to be printed
 *
 * Return: nothing
 */
void itputs(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}
