#include "shell.h"

/**
 * inbuf - input buffer command
 * @data: data structure
 * @buf: buffer
 * @leng: variable length
 *
 * Return: bytes read
 */
ssize_t inbuf(data_dt *data, char **buf, size_t *leng)
{
	ssize_t rd = 0;
	size_t pleng = 0;

	if (!*leng)
	{
		/*mfree((void **)data->cmnd_buff);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sig_handler);
#if USE_GETLINE
		rd = getline(buf, &pleng, stdin);
#else
		rd = _getline(data, buf, &pleng);
#endif
		if (rd > 0)
		{
			if ((*buf)[rd - 1] == '\n')
			{
				(*buf)[rd - 1] = '\0';
				rd--;
			}
			data->linec_f = 1;
			rmv_cmnts(*buf);
			list_hist(data, *buf, data->c_hist++);
			/* if (str_char(*buf, ';'))*/
			{
				*leng = rd;
				data->cmnd_buff = buf;
			}
		}
	}
	return (rd);
}
/**
 * gets_in - gets line
 * @data: data
 *
 * Return: bytes read
 */
ssize_t gets_in(data_dt *data)
{
	char **buf_p = &(data->arg), *ptr;
	static size_t x, y, l;
	static char *buf;
	ssize_t rd = 0;

	_putchar(BUFF);
	rd = inbuf(data, &buf, &l);
	if (rd == -1)
	return (-1);
	if (l)
	{
		y = x;
		ptr = buf + x;

		chain_check(data, buf, &y, x, l);
		while (y < l)
		{
			if (chain_delim(data, buf, &y))
					break;
				y++;
		}
		x = y + 1;
		if (x >= l)
		{
			x = l = 0;
			data->cmd_buft = CMD_;
		}
		*buf_p = ptr;
		return (str_leng(ptr));
	}
	*buf_p = buf;
	return (rd);
}
/**
 * read_buf - reads buffer
 * @data: data structure
 * @buf: buffer
 * @s: size
 *
 * Return: rd
 */
ssize_t read_buf(data_dt *data, char *buf, size_t *s)
{
	ssize_t rd = 0;

	if (*s)
	{
		return (0);
	}
	rd = read(data->rfd, buf, READ_BUFF);
	if (rd >= 0)
		*s = rd;
	return (rd);
}
/**
 * _getline - gets next line of input
 * @data: data structure
 * @ptr: pointer
 * @leng: length
 *
 * Return: string input
 */
int _getline(data_dt *data, char **ptr, size_t *leng)
{
	static char buf[READ_BUFF];
	static size_t x, l;
	size_t y;
	ssize_t rd = 0, str = 0;
	char *p = NULL, *pnew = NULL, *c;

	p = *ptr;
	if (p && leng)
		str = *leng;
	if (x == l)
		x = l = 0;
	rd = read_buf(data, buf, &l);
	if (rd == -1 || (rd == 0 && l == 0))
		return (-1);
	c = str_char(buf + x, '\n');
	y = c ? 1 + (unsigned int)(c - buf) : l;
	pnew = _realloc(p, str, str ? str + y : y - x);
	if (!pnew)
	{
		return (p ? free(p), -1 : -1);
	}
	if (str)
		cat_str(pnew, buf + x, y - x);
	else
		cpy_str(pnew, buf + x, y - x + 1);
	str += y - x;
	x = y;
	p = pnew;

	if (leng)
		*leng = str;
	*ptr = p;
	return (str);
}
/**
 * sig_handler - block cntrl c
 * @sig_num: signal number
 *
 * Return: void
 */
void sig_handler(__attribute__((unused))int sig_num)
{
	itputs("\n");
	itputs("$ ");
	_putchar(BUFF);
}
