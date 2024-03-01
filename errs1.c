#include "shell.h"

/**
 * err_stoi - converts string to integer
 * @st: string
 *
 * Return: 0 if no number found, -1 on error or converted number
 */
int err_stoi(char *st)
{
	int x = 0;
	unsigned long int  res = 0;

	if (*st == '+')
		st++;
	for (x = 0; st[x] != '\0'; x++)
	{
		if (st[x] >= '0' && st[x] <= '9')
		{
			res *= 10;
			res += (st[x] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}
/**
 * print_dec - prints a decimal number
 * @in: input
 * @fd: file descriptor
 *
 * Return: number of characters printed
 */
int print_dec(int in, int fd)
{
	int x, cnt = 0;
	unsigned int curr, abs;
	int (*_putchar_)(char) = _putchar;

	if (fd == STDERR_FILENO)
		_putchar_ = _putcharerr;
	if (in < 0)
	{
		abs = -in;
		_putchar_('-');
		cnt++;
	}
	else
		abs = in;
	curr = abs;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (abs / x)
		{
			_putchar_('0' + curr / x);
			cnt++;
		}
		curr %= x;
	}
	_putchar_('0' + curr);
	cnt++;
	return (cnt);
}
/**
 * print_err - print error message
 * @data: data structure
 * @str_err: string containing error
 *
 * Return: -1 on error, 0 if no error in string.
 */
void print_err(data_dt *data, char *str_err)
{
	puts_err(data->fname);
	puts_err(": ");
	print_dec(data->linec, STDERR_FILENO);
	puts_err(": ");
	puts_err(data->argv[0]);
	puts_err(": ");
	puts_err(str_err);
}
/**
 * itconverts - converter function
 * @num: number
 * @b: base
 * @f: argument flags
 *
 * Return: string
 */
char *itconverts(long int num, int b, int f)
{
	unsigned int n = num;
	static char buffer[50];
	static char *arr;
	char sign = 0;
	char *ptr;

	if (!(f & CNVRT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	arr = f & CNVRT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = arr[n % b];
		n /= b;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}
/**
 * rmv_cmnts - removes instances of '#'
 * @buf: address of string to be modified
 *
 * Return: Always 0
 */
void rmv_cmnts(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
		if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
}
