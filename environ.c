#include "shell.h"

/**
 * penv - prints the current environment
 * @data: data structure
 *
 * Return: always 0
 */
int penv(data_dt *data)
{
	list_strs(data->env);
	return (0);
}
/**
 * _getenv - gets the value of an environment variable
 * @data: data structure
 * @nvar: variable name
 *
 * Return: value
 */
char *_getenv(data_dt *data, const char *nvar)
{
	list_dt *nd = data->env;
	char *ptr;

	while (nd)
	{
		ptr = itstarts(nd->str, nvar);
		if (ptr && *ptr)
			return (ptr);
		nd = nd->next;
	}
	return (NULL);
}
/**
 * psetenv - sets a new environment
 * @data: data structure
 *
 * Return: always 0
 */
int psetenv(data_dt *data)
{
	if (data->argc != 3)
	{
		puts_err("Incorrect number of arguments.\n");
		return (1);
	}
	if (_setenv_(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}
/**
 * punsetenv - unset environ variable
 * @data: data structure
 *
 * Return: always 0
 */
int punsetenv(data_dt *data)
{
	int x;

	if (data->argc == 1)
	{
		puts_err("Too few arguments.\n");
		return (1);
	}
	for (x = 1; x <= data->argc; x++)
		_unsetenv_(data, data->argv[x]);
	return (0);
}
/**
 * penv_list - populates environ linked list
 * @data: data structure
 *
 * Return: always 0
 */
int penv_list(data_dt *data)
{
	list_dt *nd = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		node_end(&nd, environ[x], 0);
	data->env = nd;
	return (0);
}
