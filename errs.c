#include "shell.h"

/**
 * puts_err - prints input string
 * @str: string
 *
 * Return: nothing
 */
void puts_err(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putcharerr(str[x]);
		x++;
	}
}
/**
 * _putcharerr - writes character to stderr
 * @c: character input
 *
 * Return: 1 on success, -1 on error and errno is set appropriately
 */
int _putcharerr(char c)
{
	static int x;
	static char buf[WRITE_BUFF];

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
 * wr_fd - writes character to given fd
 * @c: character to print
 * @fd: given filedescriptor
 *
 * Return: 1 on success, -1 on error and errno is set appropriately
 */
int wr_fd(char c, int fd)
{
	static int x;
	static char buf[WRITE_BUFF];

	if (c == BUFF || x >= WRITE_BUFF)
	{
		write(fd, buf, x);
		x = 0;
	}
	if (c != BUFF)
		buf[x++] = c;
	return (1);
}
/**
 * _putsfd - prints an input string
 * @str: string to be printed
 * @fd: file descriptor
 *
 * Return: number of characters put
 */
int _putsfd(char *str, int fd)
{
	int x = 0;

	if (!str)
		return (0);
	while (*str)
	{
		x += wr_fd(*str++, fd);
	}
	return (x);
}
