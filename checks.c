#include "shell.h"

/**
 * chain_delim - test if the current char in the buffer is a chain delimiter
 * @data: parameter structure
 * @buf: character buffer
 * @pntr: pointer
 *
 * Return: 1 if correct, 0 otherwise
 */
int chain_delim(data_dt *data, char *buf, size_t *pntr)
{
	size_t y = *pntr;

	if (buf[y] == '|' && buf[y + 1] == '|')
	{
		buf[y] = 0;
		y++;
		data->cmd_buft = CMD_OR;
	}
	else if (buf[y] == '&' && buf[y + 1] == '&')
	{
		buf[y] = 0;
		y++;
		data->cmd_buft = CMD_AND;
	}
	else if (buf[y] == ';')
	{
		buf[y] = 0;
		data->cmd_buft = CMD_CHAIN;
	}
	else
		return (0);
	*pntr = y;
	return (1);
}
/**
 * chain_check - checks if we can continue chaining based on the last stats
 * @data: parameter structure
 * @buf: character buffer
 * @pntr: pointer
 * @x: buffer starting point
 * @leng: buffer length
 *
 * Return: void
 */
void chain_check(data_dt *data, char *buf, size_t *pntr, size_t x, size_t leng)
{
	size_t y = *pntr;

	if (data->cmd_buft == CMD_AND)
	{
		if (data->stats)
		{
			buf[x] = 0;
			y = leng;
		}
	}
	if (data->cmd_buft == CMD_OR)
	{
		if (!data->stats)
		{
			buf[x] = 0;
			y = leng;
		}
	}
	*pntr = y;
}
