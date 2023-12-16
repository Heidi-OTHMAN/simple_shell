#include "myshell.h"

/**
 * _unsenv - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @va: the string env var property
 */
int _unsenv(info_t *inf, char *va)
{
	list_t *nod = inf->enviro;
	size_t u = 0;
	char *b;

	if (!nod || !va)
		return (0);

	while (nod)
	{
		b = start_with(nod->string, va);
		if (b && *b == '=')
		{
			inf->env_chng = del_nod_at_inx(&(inf->enviro), u);
			u = 0;
			nod = inf->enviro;
			continue;
		}
		nod = nod->nxt;
		u++;
	}
	return (inf->env_chng);
}

/**
 * get_enviro - returns the string array copy of our environ
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_enviro(info_t *inf)
{
	if (!inf->enviroon || inf->env_chng)
	{
		inf->enviroon = lst_to_str(inf->enviro);
		inf->env_chng = 0;
	}

	return (inf->enviroon);
}

/**
 * _senv - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @va: the string env var property
 * @valu: the string env var value
 *  Return: Always 0
 */
int _senv(info_t *inf, char *va, char *valu)
{
	char *buff = NULL;
	list_t *nod;
	char *b;

	if (!va || !valu)
		return (0);

	buff = malloc(_slen(va) + _slen(valu) + 2);
	if (!buff)
		return (1);
	_scpy(buff, va);
	_scat(buff, "=");
	_scat(buff, valu);
	nod = inf->enviro;
	while (nod)
	{
		b = start_with(nod->string, va);
		if (b && *b == '=')
		{
			free(nod->string);
			nod->string = buff;
			inf->env_chng = 1;
			return (0);
		}
		nod = nod->nxt;
	}
	ad_nod_end(&(inf->enviro), buff, 0);
	free(buff);
	inf->env_chng = 1;
	return (0);
}
