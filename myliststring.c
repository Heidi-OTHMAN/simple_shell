#include "myshell.h"

/**
 * ad_nod_end - adds a node to the end of the list
 * @hd: address of pointer to head node
 * @string: str field of node
 * @numb: node index used by history
 *
 * Return: size of list
 */
list_t *ad_nod_end(list_t **hd, const char *string, int numb)
{
	list_t *new_nod, *nod;

	if (!hd)
		return (NULL);

	nod = *hd;
	new_nod = malloc(sizeof(list_t));
	if (!new_nod)
		return (NULL);
	_memst((void *)new_nod, 0, sizeof(list_t));
	new_nod->numb = numb;
	if (string)
	{
		new_nod->string = _strup(string);
		if (!new_nod->string)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->nxt)
			nod = nod->nxt;
		nod->nxt = new_nod;
	}
	else
		*hd = new_nod;
	return (new_nod);
}

/**
 * prnt_lst_str - prints only the str element of a list_t linked list
 * @g: pointer to first node
 *
 * Return: size of list
 */
size_t prnt_lst_str(const list_t *g)
{
	size_t u = 0;

	while (g)
	{
		_puuts(g->string ? g->string : "(nil)");
		_puuts("\n");
		g = g->nxt;
		u++;
	}
	return (u);
}

/**
 * ad_nod - adds a node to the start of the list
 * @hd: address of pointer to head node
 * @string: str field of node
 * @numb: node index used by history
 *
 * Return: size of list
 */
list_t *ad_nod(list_t **hd, const char *string, int numb)
{
	list_t *new_hd;

	if (!hd)
		return (NULL);
	new_hd = malloc(sizeof(list_t));
	if (!new_hd)
		return (NULL);
	_memst((void *)new_hd, 0, sizeof(list_t));
	new_hd->numb = numb;
	if (string)
	{
		new_hd->string = _strup(string);
		if (!new_hd->string)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->nxt = *hd;
	*hd = new_hd;
	return (new_hd);
}

/**
 * del_nod_at_inx - deletes node at given index
 * @hd: address of pointer to first node
 * @inx: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int del_nod_at_inx(list_t **hd, unsigned int inx)
{
	list_t *nod, *prev_nod;
	unsigned int u = 0;

	if (!hd || !*hd)
		return (0);

	if (!inx)
	{
		nod = *hd;
		*hd = (*hd)->nxt;
		free(nod->string);
		free(nod);
		return (1);
	}
	nod = *hd;
	while (nod)
	{
		if (u == inx)
		{
			prev_nod->nxt = nod->nxt;
			free(nod->string);
			free(nod);
			return (1);
		}
		u++;
		prev_nod = nod;
		nod = nod->nxt;
	}
	return (0);
}

/**
 * fr_list - frees all nodes of a list
 * @hd_poin: address of pointer to head node
 *
 * Return: void
 */
void fr_list(list_t **hd_poin)
{
	list_t *nod, *next_nod, *hd;

	if (!hd_poin || !*hd_poin)
		return;
	hd = *hd_poin;
	nod = hd;
	while (nod)
	{
		next_nod = nod->nxt;
		free(nod->string);
		free(nod);
		nod = next_nod;
	}
	*hd_poin = NULL;
}
