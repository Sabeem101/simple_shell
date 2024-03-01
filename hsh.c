#include "shell.h"

/**
 * hsh - main shell loop
 * @data: data
 * @av: argv
 *
 * Return: O on success, 1 on error
 */
int hsh(data_dt *data, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_dt(data);
		if (interact(data))
			itputs("$ ");
		_putcharerr(BUFF);
		r = gets_in(data);
		if (r != -1)
		{
			set_dt(data, av);
			builtin_ret = loc_bltin(data);
			if (builtin_ret == -1)
				loc_cmd(data);
		}
		else if (interact(data))
			_putchar('\n');
		free_dt(data, 0);
	}
	wr_hist(data);
	free_dt(data, 1);
	if (!interact(data) && data->stats)
		exit(data->stats);
	if (builtin_ret == -2)
	{
		if (data->nerr == -1)
			exit(data->stats);
		exit(data->nerr);
	}
	return (builtin_ret);
}
/**
 * loc_bltin - find builtin command
 * @data: data structure
 *
 * Return: 1 if cmd found but not successful
 *              0 if cmd found and executed succesfully
 */
int loc_bltin(data_dt *data)
{
	int x, built_in_ret = -1;
	bltin builtintbl[] = {
		{"exit", pexit},
		{"env", penv},
		{"help", phelp},
		{"histoy", phistory},
		{"setenv", psetenv},
		{"unseten", punsetenv},
		{"cd", pcd},
		{"alias", palias},
		{NULL, NULL}
	};
	for (x = 0; builtintbl[x].type; x++)
		if (_strcmp(data->argv[0], builtintbl[x].type) == 0)
		{
			data->linec++;
			built_in_ret = builtintbl[x].func(data);
			break;
		}
	return (built_in_ret);
}
/**
 * loc_cmd - locates a command in path
 * @data: data structure
 *
 * Return: void
 */
void loc_cmd(data_dt *data)
{
	char *path = NULL;
	int x, y;

	data->path = data->argv[0];
	if (data->linec_f == 1)
	{
		data->linec++;
		data->linec_f = 0;
	}
	for (x = 0, y = 0; data->arg[x]; x++)
		if (!__delim(data->arg[x], " \t\n"))
			y++;
	if (!y)
		return;
	path = fpath(data, _getenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		frk_cmd(data);
	}
	else
	{
		if ((interact(data) || _getenv(data, "PATH=")
				|| data->argv[0][0] == '/') && cmnd(data, data->argv[0]))
			frk_cmd(data);
		else if (*(data->arg) != '\n')
		{
			data->stats = 127;
			print_err(data, "not found\n");
		}
	}
}
/**
 * frk_cmd - forks thread to run an executable command
 * @data: data structure
 *
 * Return: void
 */
void frk_cmd(data_dt *data)
{
	pid_t cpid;

	cpid = fork();
	if (cpid == -1)
	{
		perror("Error:");
		return;
	}
	if (cpid == 0)
	{
		if (execve(data->path, data->argv, _getenv_(data)) == -1)
		{
			free_dt(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->stats));
		if (WIFEXITED(data->stats))
		{
			data->stats = WEXITSTATUS(data->stats);
			if (data->stats == 126)
				print_err(data, "Permission denied\n");
		}
	}
}
