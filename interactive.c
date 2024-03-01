#include "shell.h"

/**
 * interact - returns true id shell is in interactive mode
 * @data: struct address
 *
 * Return: 1 if interact mode, 0 otherwise
 */
int interact(data_dt *data)
{
	return (isatty(STDIN_FILENO) && data->rfd <= 2);
}
/**
 * __delim - checks if character is a delimiter
 * @c: character
 * @delim: delimiter string
 *
 * Return: 1 if true, 0 if false
 */
int __delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
/**
 * __alpha - checks for alphabetic character
 * @c: the character to input
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int __alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * intostr - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */
int intostr(char *s)
{
	int x, sign = 1, flag = 0, output;
	unsigned int res = 0;

	for (x = 0; s[x] != '\0' && flag != 2; x++)
	{
		if (s[x] == '-')
		{
			sign *= -1;
		}
		if (s[x] >= '0' && s[x] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (s[x] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -res;
	else
		output = res;
	return (output);
}
