#include "shell.h"

/**
 * phistory - displays history list
 * @data: data structure
 *
 * Return: always 0
 */
int phistory(data_dt *data)
{
	list_print(data->history);
	return (0);
}
/**
 * _unsets_alias_ - unsets alias
 * @data: data structure
 * @str: string
 *
 * Return: 0 on success, 1 if failed
 */
int _unsets_alias_(data_dt *data, char *str)
{
	char c, *ptr;
	int ret;

	ptr = str_char(str, '=');
	if (!ptr)
	{
		return (1);
	}
	c = *ptr;
	*ptr = 0;
	ret = rmv_node(&(data->alias),
			nindex(data->alias, itstarts_node(data->alias, str, -1)));
	*ptr = c;
	return (ret);
}
/**
 * _sets_alias_ - sets alias
 * @data: data structure
 * @str: string
 *
 * Return: 0 on success, 1 if failed
 */
int _sets_alias_(data_dt *data, char *str)
{
	char *ptr;

	ptr = str_char(str, '=');
	if (!ptr)
	{
		return (1);
	}
	if (!*++ptr)
		return (_unsets_alias_(data, str));

	_unsets_alias_(data, str);
	return (node_end(&(data->alias), str, 0) == NULL);
}
/**
 * _print_alias_ - prints the alias
 * @nd: alias node
 *
 * Return: 0 on success, 1 if failed
 */
int _print_alias_(list_dt *nd)
{
	char *ptr = NULL;
	char *al = NULL;

	if (nd)
	{
		ptr = str_char(nd->str, '=');
		for (al = nd->str; al <= ptr; al++)
			_putchar(*al);
		_putchar('\'');
		itputs(ptr + 1);
		itputs("'\n");
		return (0);
	}
	return (1);
}
/**
 * palias - same as the builtin alias
 * @data: data structure
 *
 * Return: always 0
 */
int palias(data_dt *data)
{
	int x = 0;
	char *ptr = NULL;
	list_dt *nd = NULL;

	if (data->argc == 1)
	{
		nd = data->alias;
		while (nd)
		{
			_print_alias_(nd);
			nd = nd->next;
		}
		return (0);
	}
	for (x = 1; data->argv[x]; x++)
	{
		ptr = str_char(data->argv[x], '=');
		if (ptr)
			_sets_alias_(data, data->argv[x]);
		else
			_print_alias_(itstarts_node(data->alias, data->argv[x], '='));
	}
	return (0);
}
