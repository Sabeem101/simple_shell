#include "shell.h"

/**
 * list_leng - length of linked list
 * @frst: pointer to first node
 *
 * Return: size of list
 */
size_t list_leng(const list_dt *frst)
{
	size_t x = 0;

	while (frst)
	{
		frst = frst->next;
		x++;
	}
	return (x);
}
/**
 * list_arr - array of strings of the list
 * @hd: pointer to first node
 *
 * Return: array of strings
 */
char **list_arr(list_dt *hd)
{
	list_dt *nd = hd;
	size_t y, x = list_leng(hd);
	char **strns;
	char *str;

	if (!hd || !x)
	{
		return (NULL);
	}
	strns = malloc(sizeof(char *) * (x + 1));
	if (!strns)
	{
		return (NULL);
	}
	for (x = 0; nd; nd = nd->next, x++)
	{
		str = malloc(str_leng(nd->str) + 1);
		if (!str)
		{
			for (y = 0; y < x; y++)
				free(strns[y]);
			free(strns);
			return (NULL);
		}
		str = _strcpy(str, nd->str);
		strns[x] = str;
	}
	strns[x] = NULL;
	return (strns);
}
/**
 * list_print - prints all elements of a linked list
 * @fnp: pointer to first node
 *
 * Return: size of list
 */
size_t list_print(const list_dt *fnp)
{
	size_t x = 0;

	while (fnp)
	{
		itputs(itconverts(fnp->nex, 10, 0));
		_putchar(':');
		_putchar(' ');
		itputs(fnp->str ? fnp->str : "(nil)");
		itputs("\n");
		fnp = fnp->next;
		x++;
	}
	return (x);
}
/**
 * itstarts_node - returns node that starts with prefix
 * @node: pointer to head list
 * @prefix: string to match
 * @c: character
 *
 * Return: match node or null
 */
list_dt *itstarts_node(list_dt *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = itstarts(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * nindex - gets the index of a node
 * @hf: list head
 * @nd: node
 *
 * Return: index or -1
 */
ssize_t nindex(list_dt *hf, list_dt *nd)
{
	size_t x = 0;

	while (hf)
	{
		if (hf == nd)
		{
			return (x);
		}
		hf = hf->next;
		x++;
	}
	return (-1);
}
