#include "shell.h"

/**
 * str_tok - splits string into words
 * @str: string
 * @d: delimiter
 *
 * Return: pointer to an array of string, or NULL
 */
char **str_tok(char *str, char *d)
{
	int w, x, y, z, numw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (w = 0; str[w] != '\0'; w++)
		if (!__delim(str[w], d) && (__delim(str[w + 1], d) || !str[w + 1]))
			numw++;
	if (numw == 0)
		return (NULL);
	s = malloc((1 + numw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (w = 0, x = 0; x < numw; x++)
	{
		while (__delim(str[w], d))
			w++;
		y = 0;
		while (!__delim(str[w + y], d) && str[w + y])
			y++;
		s[x] = malloc((y + 1) * sizeof(char));
		if (!s[x])
		{
			for (y = 0; y < x; y++)
				free(s[y]);
			free(s);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			s[x][z] = str[w++];
		s[x][z] = 0;
	}
	s[x] = NULL;
	return (s);
}
/**
 * tok_strn - splits a string into words
 * @str: string
 * @d: delimiter
 *
 * Return: pointer to an array of strings, or NULL
 */
char **tok_strn(char *str, char d)
{
	int a, b, c, e, numw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				(str[a] != d && !str[a + 1]) || str[a + 1] == d)
			numw++;
	if (numw == 0)
		return (NULL);
	s = malloc((1 + numw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numw; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != d && str[a + c] != d)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < c; e++)
			s[b][e] = str[a++];
		s[b][e] = 0;
	}
	s[b] = NULL;
	return (s);
}
