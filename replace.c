#include "shell.h"

/**
 * replace_alias - replaces alias in tokenized string
 * @data: parameter structure
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(data_dt *data)
{
	list_dt *node;
	char *pntr;
	int x;

	for (x = 0; x < 10; x++)
	{
		node = itstarts_node(data->alias, data->argv[0], '=');
		if (!node)
			return (0);
		free(data->argv[0]);
		pntr = str_char(node->str, '=');
		if (!pntr)
		{
			return (0);
		}
		pntr = _strdup(pntr + 1);
		if (!pntr)
			return (0);
		data->argv[0] = pntr;
	}
	return (1);
}
/**
 * replace_str - replaces string
 * @old: old string address
 * @n: new string
 *
 * Return: 1 if replaced, 0 if failed
 */
int replace_str(char **old, char *n)
{
	free(*old);
	*old = n;
	return (1);
}
/**
 * replace_vars - replaces variables in tokenized string
 * @data: parameter structure
 *
i * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(data_dt *data)
{
	int x = 0;
	list_dt *node;

	for (x = 0; data->argv[x]; x++)
	{
		if (data->argv[x][0] != '$' || !data->argv[x][1])
			continue;
		if (_strcmp(data->argv[x], "$?"))
		{
			replace_str(&(data->argv[x]),
					_strdup(itconverts(getpid(), 10, 0)));
			continue;
		}
		node = itstarts_node(data->env, &data->argv[x][1], '=');
		if (node)
		{
			replace_str(&(data->argv[x]),
					_strdup(str_char(node->str, '=') + 1));
			continue;
		}
		replace_str(&data->argv[x], _strdup(""));
	}
	return (0);
}
