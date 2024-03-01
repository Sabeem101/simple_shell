#include "shell.h"

/**
 * cmnd - determines if a file is executable
 * @data: data structure
 * @path: file path
 *
 * Return: 1 on success, 0 otherwise
 */
int cmnd(data_dt *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * chars_dp - duplicates characters
 * @path_str: path string
 * @begin: index begining
 * @end: index ending
 *
 * Return: pointer to nex buffer
 */
char *chars_dp(char *path_str, int begin, int end)
{
	static char buf[1024];
	int x = 0, y = 0;

	for (y = 0, x = begin; x < end; x++)
		if (path_str[x] != ':')
			buf[y++] = path_str[x];
	buf[y] = 0;
	return (buf);
}
/**
 * fpath - finds command in the path string
 * @data: data structure
 * @path_str: path string
 * @cmd: command to find
 *
 * Return: full path of command if found or NULL
 */
char *fpath(data_dt *data, char *path_str, char *cmd)
{
	int x = 0, pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((str_leng(cmd) > 2) && itstarts(cmd, "./"))
	{
		if (cmnd(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[x] || path_str[x] == ':')
		{
			path = chars_dp(path_str, pos, x);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (cmnd(data, path))
				return (path);
			if (!path_str[x])
				break;
			pos = x;
		}
		x++;
	}
	return (NULL);
}
