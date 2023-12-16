#include "myshell.h"

/**
 * bfr - frees a pointer and NULLs the address
 * @poin: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfr(void **poin)
{
	if (poin && *poin)
	{
		free(*poin);
		*poin = NULL;
		return (1);
	}
	return (0);
}
