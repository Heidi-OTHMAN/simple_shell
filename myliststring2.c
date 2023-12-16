#include "myshell.h"

/**
 * lst_to_str - returns an array of strings of the list->str
 * @hd: pointer to first node
 *
 * Return: array of strings
 */
char **lst_to_str(list_t *hd)
{
	list_t *nod = hd;
	size_t u = list_ln(hd), s;
	char **stra;
	char *strr;

	if (!hd || !u)
		return (NULL);
	stra = malloc(sizeof(char *) * (u + 1));
	if (!stra)
		return (NULL);
	for (u = 0; nod; nod = nod->nxt, u++)
	{
		strr = malloc(_slen(nod->string) + 1);
		if (!strr)
		{
			for (s = 0; s < u; s++)
				free(stra[s]);
			free(stra);
			return (NULL);
		}

		strr = _scpy(strr, nod->string);
		stra[u] = strr;
	}
	stra[u] = NULL;
	return (stra);
}


/**
 * prnt_lst - prints all elements of a list_t linked list
 * @g: pointer to first node
 *
 * Return: size of list
 */
size_t prnt_lst(const list_t *g)
{
	size_t u = 0;

	while (g)
	{
		_puuts(conv_number(g->numb, 10, 0));
		_ptchr(':');
		_ptchr(' ');
		_puuts(g->string ? g->string : "(nil)");
		_puuts("\n");
		g = g->nxt;
		u++;
	}
	return (u);
}

/**
 * list_ln - determines length of linked list
 * @g: pointer to first node
 *
 * Return: size of list
 */
size_t list_ln(const list_t *g)
{
	size_t u = 0;

	while (g)
	{
		g = g->nxt;
		u++;
	}
	return (u);
}

/**
 * nod_start_with - returns node whose string starts with prefix
 * @nod: pointer to list head
 * @pfix: string to match
 * @m: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *nod_start_with(list_t *nod, char *pfix, char m)
{
	char *b = NULL;

	while (nod)
	{
		b = start_with(nod->string, pfix);
		if (b && ((m == -1) || (*b == m)))
			return (nod);
		nod = nod->nxt;
	}
	return (NULL);
}

/**
 * get_nod_inx - gets the index of a node
 * @hd: pointer to list head
 * @nod: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_nod_inx(list_t *hd, list_t *nod)
{
	size_t u = 0;

	while (hd)
	{
		if (hd == nod)
			return (u);
		hd = hd->nxt;
		u++;
	}
	return (-1);
}
