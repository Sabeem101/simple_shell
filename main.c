#include "shell.h"

/**
 * main - shell entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, 1 if failed
 */
int main(int ac, char **av)
{
	data_dt data[] = { DATA_INIT };
	int fd = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				puts_err(av[0]);
				puts_err(": 0: Can't open ");
				puts_err(av[1]);
				_putcharerr('\n');
				_putcharerr(BUFF);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->rfd = fd;
	}
	penv_list(data);
	rd_hist(data);
	hsh(data, av);
	return (EXIT_SUCCESS);
}
