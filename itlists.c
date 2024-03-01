#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: pointer to the head node
 * @str: string field of node
 * @nex: node index
 *
 * Return: size of list
 */
list_dt *add_node(list_dt **head, const char *str, int nex)
{
	list_dt *nhead;

	if (!head)
	{
		return (NULL);
	}
	nhead = malloc(sizeof(list_dt));
	if (!nhead)
		return (NULL);
	mem_sets((void *)nhead, 0, sizeof(list_dt));
	nhead->nex = nex;
	if (str)
	{
		nhead->str = _strdup(str);
		if (!nhead->str)
		{
			free(nhead);
			return (NULL);
		}
	}
	nhead->next = *head;
	*head = nhead;
	return (nhead);
}
/**
 * node_end - adds a node to the end of the list
 * @head: pointer to the head node
 * @str: string of the node
 * @nex: node index
 *
 * Return: size of list
 */
list_dt *node_end(list_dt **head, const char *str, int nex)
{
	list_dt *n_node, *node;

	if (!head)
	{
		return (NULL);
	}
	node = *head;
	n_node = malloc(sizeof(list_dt));
	if (!n_node)
		return (NULL);
	mem_sets((void *)n_node, 0, sizeof(list_dt));
	n_node->nex = nex;
	if (str)
	{
		n_node->str = _strdup(str);
		if (!n_node->str)
		{
			free(n_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = n_node;
	}
	else
		*head = n_node;
	return (n_node);
}
/**
 * list_strs - prints only the string element of list_dt
 * @frst: pointer to first node
 *
 * Return: size of list
 */
size_t list_strs(const list_dt *frst)
{
	size_t x = 0;

	while (frst)
	{
		itputs(frst->str ? frst->str : "(nil)");
		itputs("\n");
		frst = frst->next;
		x++;
	}
	return (x);
}
/**
 * rmv_node - deletes node at given index
 * @head: pointer to the first node
 * @index: node index
 *
 * Return: 1 on success, 0 otherwise
 */
int rmv_node(list_dt **head, unsigned int index)
{
	list_dt *node, *prevnd;
	unsigned int x = 0;

	if (!head || !*head)
	{
		return (0);
	}
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (x == index)
		{
			prevnd->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		x++;
		prevnd = node;
		node = node->next;
	}
	return (0);
}
/**
 * free_list - frees all nodes of a list
 * @head_ptr: pointer to head node
 *
 * Return: void
 */
void free_list(list_dt **head_ptr)
{
	list_dt *nd, *next_nd, *hd;

	if (!head_ptr || *head_ptr)
		return;
	hd = *head_ptr;
	nd = hd;
	while (nd)
	{
		next_nd = nd->next;
		free(nd->str);
		free(nd);
		nd = next_nd;
	}
	*head_ptr = NULL;
}
