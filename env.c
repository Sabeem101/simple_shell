#include "shell.h"

/**
 * _getenv_ - returns string array copy of environ
 * @data: data structure
 *
 * Return: always 0
 */
char **_getenv_(data_dt *data)
{
	if (!data->environ || data->ch_env)
	{
		data->environ = list_arr(data->env);
		data->ch_env = 0;
	}
	return (data->environ);
}
/**
 * _unsetenv_ - remove environment variable
 * @data: data structure
 * @var: environment variable
 *
 * Return: 1 if removed, 0 otherwise
 */
int _unsetenv_(data_dt *data, char *var)
{
	list_dt *nd = data->env;
	size_t x = 0;
	char *ptr;

	if (!nd || !var)
		return (0);
	while (nd)
	{
		ptr = itstarts(nd->str, var);
		if (ptr && *ptr == '=')
		{
			data->ch_env = rmv_node(&(data->env), x);
			x = 0;
			nd = data->env;
			continue;
		}
		nd = nd->next;
		x++;
	}
	return (data->ch_env);
}
/**
 * _setenv_ - start a new environment or modify and existing one
 * @data: data structure
 * @var: variable
 * @val: value
 *
 * Return: always 0
 */
int _setenv_(data_dt *data, char *var, char *val)
{
	char *buf = NULL;
	list_dt *nd;
	char *ptr;

	if (!var || !val)
	{
		return (0);
	}
	buf = malloc(str_leng(var) + str_leng(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, val);
	nd = data->env;
	while (nd)
	{
		ptr = itstarts(nd->str, var);
		if (ptr && *ptr == '=')
		{
			free(nd->str);
			nd->str = buf;
			data->ch_env = 1;
			return (0);
		}
		nd = nd->next;
	}
	node_end(&(data->env), buf, 0);
	free(buf);
	data->ch_env = 1;
	return (0);
}
