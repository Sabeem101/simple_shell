#include "shell.h"

/**
 * set_dt - initializes data structure
 * @data: structure address
 * @av: argument vector
 *
 * Return: void
 */
void set_dt(data_dt *data, char **av)
{
	int x = 0;

	data->fname = av[0];
	if (data->arg)
	{
		data->argv = str_tok(data->arg, " \t");
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (x = 0; data->argv && data->argv[x]; x++)
			;
		data->argc = x;
		replace_alias(data);
		replace_vars(data);
	}
}
/**
 * clear_dt - clears data structure
 * @data: structure address
 *
 * Return: void
 */
void clear_dt(data_dt *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}
/**
 * free_dt - frees data
 * @data: structure address
 * @all: frees all
 *
 * Return: void
 */
void free_dt(data_dt *data, int all)
{
	_frees(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (all)
	{
		if (!data->cmnd_buff)
			free(data->arg);
		if (data->env)
			free_list(&(data->history));
		if (data->alias)
			free_list(&(data->alias));
		_frees(data->environ);
		data->environ = NULL;
		mfree((void **)data->cmnd_buff);
		if (data->rfd > 2)
			close(data->rfd);
		_putchar(BUFF);
	}
}
