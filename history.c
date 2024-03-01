#include "shell.h"

/**
 * hist_file - getsthe history file
 * @data: data structure
 *
 * Return: string containing history file
 */
char *hist_file(data_dt *data)
{
	char *buf, *dir;

	dir = _getenv(data, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (str_leng(dir) + str_leng(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}
/**
 * wr_hist - creates files or appends existing ones
 * @data: parameter structure
 *
 * Return: 1 on success, -1 if failed
 */
int wr_hist(data_dt *data)
{
	ssize_t fd;
	char *filename = hist_file(data);
	list_dt *nd = NULL;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (nd = data->history; nd; nd = nd->next)
	{
		_putsfd(nd->str, fd);
		wr_fd('\n', fd);
	}
	wr_fd(BUFF, fd);
	close(fd);
	return (1);
}
/**
 * list_hist - adds entry to a linked list
 * @data: data structure
 * @buf: buffer
 * @line_count: line count
 *
 * Return: always 0
 */
int list_hist(data_dt *data, char *buf, int line_count)
{
	list_dt *nd = NULL;

	if (data->history)
		nd = data->history;
	node_end(&nd, buf, line_count);

	if (!data->history)
		data->history = nd;
	return (0);
}
/**
 * rnum_hist - renumbers linked list
 * @data: data structure
 *
 * Return: next history count
 */
int rnum_hist(data_dt *data)
{
	list_dt *nd = data->history;
	int x = 0;

	while (nd)
	{
		nd->nex = x++;
		nd = nd->next;
	}
	return (data->c_hist = x);
}
/**
 * rd_hist - reads history
 * @data: parameter structure
 *
 * Return: c_hist on succes, 0 if failed
 */
int rd_hist(data_dt *data)
{
	int x, l, line_count = 0;
	ssize_t fd, rdleng, fsize = 0;
	char *buf = NULL, *filename = hist_file(data);
	struct stat st;

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdleng = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdleng <= 0)
		return (free(buf), 0);
	close(fd);
	for (x = 0; x < fsize; x++)
		if (buf[x] == '\n')
		{
			buf[x] = 0;
			list_hist(data, buf + l, line_count++);
			l = x + 1;
		}
	if (l != x)
		list_hist(data, buf + l, line_count++);
	free(buf);
	data->c_hist = line_count;
	while (data->c_hist-- >= HIST_MAX)
		rmv_node(&(data->history), 0);
	rnum_hist(data);
	return (data->c_hist);
}
