#include "myshell.h"

/**
 * chk_chain - checks we should continue chaining based on last status
 * @inf: the parameter struct
 * @buff: the char buffer
 * @b: address of current position in buf
 * @s: starting position in buf
 * @le: length of buf
 *
 * Return: Void
 */
void chk_chain(info_t *inf, char *buff, size_t *b, size_t s, size_t le)
{
	size_t k = *b;

	if (inf->cmd_buff_typ == CMD_AND)
	{
		if (inf->stats)
		{
			buff[s] = 0;
			k = le;
		}
	}
	if (inf->cmd_buff_typ == CMD_OR)
	{
		if (!inf->stats)
		{
			buff[s] = 0;
			k = le;
		}
	}

	*b = k;
}

/**
 * rep_alias - replaces an aliases in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_alias(info_t *inf)
{
	int a;
	list_t *nod;
	char *b;

	for (a = 0; a < 10; a++)
	{
		nod = nod_start_with(inf->alas, inf->arggv[0], '=');
		if (!nod)
			return (0);
		free(inf->arggv[0]);
		b = _strchar(nod->string, '=');
		if (!b)
			return (0);
		b = _strup(b + 1);
		if (!b)
			return (0);
		inf->arggv[0] = b;
	}
	return (1);
}

/**
 * a_chain - test if current char in buffer is a chain delimeter
 * @inf: the parameter struct
 * @buff: the char buffer
 * @b: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int a_chain(info_t *inf, char *buff, size_t *b)
{
	size_t t = *b;

	if (buff[t] == '|' && buff[t + 1] == '|')
	{
		buff[t] = 0;
		t++;
		inf->cmd_buff_typ = CMD_OR;
	}
	else if (buff[t] == '&' && buff[t + 1] == '&')
	{
		buff[t] = 0;
		t++;
		inf->cmd_buff_typ = CMD_AND;
	}
	else if (buff[t] == ';') /* found end of this command */
	{
		buff[t] = 0; /* replace semicolon with null */
		inf->cmd_buff_typ = CMD_CHAIN;
	}
	else
		return (0);
	*b = t;
	return (1);
}

/**
 * rep_vars - replaces vars in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_vars(info_t *inf)
{
	int k = 0;
	list_t *nod;

	for (k = 0; inf->arggv[k]; k++)
	{
		if (inf->arggv[k][0] != '$' || !inf->arggv[k][1])
			continue;

		if (!_strcom(inf->arggv[k], "$?"))
		{
			rep_string(&(inf->arggv[k]),
				_strup(conv_number(inf->stats, 10, 0)));
			continue;
		}
		if (!_strcom(inf->arggv[k], "$$"))
		{
			rep_string(&(inf->arggv[k]),
				_strup(conv_number(getpid(), 10, 0)));
			continue;
		}
		nod = nod_start_with(inf->enviro, &inf->arggv[k][1], '=');
		if (nod)
		{
			rep_string(&(inf->arggv[k]),
				_strup(_strchar(nod->string, '=') + 1));
			continue;
		}
		rep_string(&inf->arggv[k], _strup(""));

	}
	return (0);
}

/**
 * rep_string - replaces string
 * @o: address of old string
 * @n: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_string(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
