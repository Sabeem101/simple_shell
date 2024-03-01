#include "shell.h"

/**
 * pexit - exits shell
 * @data: data structure
 *
 * Return: exits with given exit stats
 */
int pexit(data_dt *data)
{
	int echeck;

	if (data->argv[1])
	{
		echeck = err_stoi(data->argv[1]);
		if (echeck == -1)
		{
			data->stats = 2;
			print_err(data, "Illegal number: ");
			puts_err(data->argv[1]);
			_putcharerr('\n');
			return (1);
		}
		data->nerr = err_stoi(data->argv[1]);
		return (-2);
	}
	data->nerr = -1;
	return (-2);
}
/**
 * pcd - changes current directory
 * @data: data structure
 *
 * Return: always 0
 */
int pcd(data_dt *data)
{
	char *x, *dir, buffer[1024];
	int chdir_ret;

	x = getcwd(buffer, 1024);
	if (!x)
		itputs("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1])
	{
		dir = _getenv(data, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(data, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!_getenv(data, "OLDPWD="))
		{
			itputs(x);
			_putchar('\n');
			return (1);
		}
		itputs(_getenv(data, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _getenv(data, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(data->argv[1]);
	if (chdir_ret == -1)
	{
		print_err(data, "can't cd to ");
		puts_err(data->argv[1]), _putcharerr('\n');
	}
	else
	{
		_setenv_(data, "OLDPWD", _getenv(data, "PWD="));
		_setenv_(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * phelp - changes the current directory of the process
 * @data: data structure
 *
 * Return: always 0
 */
int phelp(data_dt *data)
{
	char **arg_arr;

	arg_arr = data->argv;
	itputs("help call works. Function not implemented.\n");
	if (0)
		itputs(*arg_arr);
	return (0);
}
