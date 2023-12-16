#include "myshell.h"

/**
 * _genv - gets the value of an environ variable
 * @inf: Structure containing potential arguments. Used to maintain
 * @nm: env var name
 *
 * Return: the value
 */
char *_genv(info_t *inf, const char *nm)
{
	list_t *nod = inf->enviro;
	char *b;

	while (nod)
	{
		b = start_with(nod->string, nm);
		if (b && *b)
			return (b);
		nod = nod->nxt;
	}
	return (NULL);
}

/**
 * _osetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _osetenv(info_t *inf)
{
	if (inf->arc != 3)
	{
		_ept("Incorrect number of arguements\n");
		return (1);
	}
	if (_senv(inf, inf->arggv[1], inf->arggv[2]))
		return (0);
	return (1);
}

/**
 * _oenv - prints the current environment
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _oenv(info_t *inf)
{
	prnt_lst_str(inf->enviro);
	return (0);
}

/**
 * _ounsetenv - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _ounsetenv(info_t *inf)
{
	int k;

	if (inf->arc == 1)
	{
		_ept("Too few arguements.\n");
		return (1);
	}
	for (k = 1; k <= inf->arc; k++)
		_unsenv(inf, inf->arggv[k]);

	return (0);
}

/**
 * pop_env_list - populates env linked list
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int pop_env_list(info_t *inf)
{
	list_t *nod = NULL;
	size_t k;

	for (k = 0; enviroon[k]; k++)
		ad_nod_end(&nod, enviroon[k], 0);
	inf->enviro = nod;
	return (0);
}
