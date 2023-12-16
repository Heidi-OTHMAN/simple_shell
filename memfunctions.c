#include "myshell.h"

/**
 * ffr - frees a string of strings
 * @bb: string of strings
 */
void ffr(char **bb)
{
	char **o = bb;

	if (!bb)
		return;
	while (*bb)
		free(*bb++);
	free(o);
}

/**
 **_memst - fills memory with a constant byte
 *@y: the pointer to the memory area
 *@p: the byte to fill *s with
 *@w: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memst(char *y, char p, unsigned int w)
{
	unsigned int u;

	for (u = 0; u < w; u++)
		y[u] = p;
	return (y);
}

/**
 * _reloc - reallocates a block of memory
 * @poin: pointer to previous malloc'ated block
 * @o_size: byte size of previous block
 * @n_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_reloc(void *poin, unsigned int o_size, unsigned int n_size)
{
	char *b;

	if (!poin)
		return (malloc(n_size));
	if (!n_size)
		return (free(poin), NULL);
	if (n_size == o_size)
		return (poin);

	b = malloc(n_size);
	if (!b)
		return (NULL);

	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		b[o_size] = ((char *)poin)[o_size];
	free(poin);
	return (b);
}
