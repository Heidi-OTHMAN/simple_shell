#include "myshell.h"

/**
 * unst_alas - sets alias to string
 * @inf: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unst_alas(info_t *inf, char *string)
{
	char *b, m;
	int retu;

	b = _strchar(string, '=');
	if (!b)
		return (1);
	m = *b;
	*b = 0;
	retu = del_nod_at_inx(&(inf->alas),
		get_nod_inx(inf->alas, node_starts_with(inf->alas, string, -1)));
	*b = m;
	return (retu);
}

/**
 * set_alas - sets alias to string
 * @inf: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alas(info_t *inf, char *string)
{
	char *b;

	b = _strchar(string, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (unst_alas(inf, string));

	unst_alas(inf, string);
	return (ad_nod_end(&(inf->alas), string, 0) == NULL);
}

/**
 * _ourhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @inf: Structure contain potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _ourhistory(info_t *inf)
{
	prnt_lst(inf->his);
	return (0);
}

/**
 * prnt_alas - prints an alias string
 * @nod: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int prnt_alas(list_t *nod)
{
	char *b = NULL, *h = NULL;

	if (nod)
	{
		b = _strchar(nod->string, '=');
		for (h = nod->string; h <= b; h++)
			_ptchr(*h);
		_ptchr('\'');
		_puuts(b + 1);
		_puuts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _ouralas - mimics the alias builtin (man alias)
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _ouralas(info_t *inf)
{
	int k = 0;
	char *b = NULL;
	list_t *nod = NULL;

	if (inf->arc == 1)
	{
		nod = inf->alas;
		while (nod)
		{
			prnt_alas(nod);
			nod = nod->nxt;
		}
		return (0);
	}
	for (k = 1; inf->arggv[k]; k++)
	{
		p = _strchar(inf->arggv[k], '=');
		if (b)
			set_alas(inf, inf->arggv[k]);
		else
			prnt_alas(nod_start_with(inf->alas, inf->arggv[k], '='));
	}

	return (0);
}
