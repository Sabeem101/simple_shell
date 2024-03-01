#include "shell.h"

/**
 * mfree - frees a pointer and nulls the address
 * @ptr: pointer to free
 *
 * Return: 1 on success, 0 if failed
 */
int mfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
