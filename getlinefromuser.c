#include "myshell.h"

/**
 * get_inpt - gets a line minus the newline
 * @inf: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_inpt(info_t *inf)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t u, s, ln;
	ssize_t d = 0;
	char **buff_p = &(inf->argg), *b;

	_ptchr(BUF_FLUSH);
	d = inpt_buff(inf, &buff, &ln);
	if (d == -1) /* EOF */
		return (-1);
	if (ln)	/* we have commands left in the chain buffer */
	{
		s = u; /* init new iterator to current buf position */
		b = buff + u; /* get pointer for return */

		chk_chain(inf, buff, &s, u, ln);
		while (s < ln) /* iterate to semicolon or end */
		{
			if (a_chain(inf, buff, &s))
				break;
			s++;
		}

		u = s + 1; /* increment past nulled ';'' */
		if (u >= ln) /* reached end of buffer? */
		{
			u = ln = 0; /* reset position and length */
			inf->cmd_buff_typ = CMD_NORM;
		}

		*buff_p = b; /* pass back pointer to current command position */
		return (_slen(b)); /* return length of current command */
	}

	*buff_p = buff; /* else not a chain, pass back buffer from _getline() */
	return (d); /* return length of buffer from _getline() */
}

/**
 * read_buff - reads a buffer
 * @inf: parameter struct
 * @buff: buffer
 * @u: size
 *
 * Return: d
 */
ssize_t read_buff(info_t *inf, char *buff, size_t *u)
{
	ssize_t d = 0;

	if (*u)
		return (0);
	d = read(inf->redfd, buff, READ_BUF_SIZE);
	if (d >= 0)
		*u = d;
	return (d);
}

/**
 * inpt_buff - buffers chained commands
 * @inf: parameter struct
 * @buff: address of buffer
 * @ln: address of len var
 *
 * Return: bytes read
 */
ssize_t inpt_buff(info_t *inf, char **buff, size_t *ln)
{
	ssize_t d = 0;
	size_t len_x = 0;

	if (!*ln) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		d = getline(buff, &len_x, stdin);
#else
		d = _getline(inf, buff, &len_x);
#endif
		if (d > 0)
		{
			if ((*buff)[d - 1] == '\n')
			{
				(*buff)[d - 1] = '\0'; /* remove trailing newline */
				d--;
			}
			inf->linecnt_flag = 1;
			rm_comments(*buff);
			build_his_lst(inf, *buff, inf->histcnt++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*ln = d;
				inf->cmd_buff = buff;
			}
		}
	}
	return (d);
}

/**
 * _gline - gets the next line of input from STDIN
 * @inf: parameter struct
 * @poin: address of pointer to buffer, preallocated or NULL
 * @len: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _gline(info_t *inf, char **poin, size_t *len)
{
	static char buff[READ_BUF_SIZE];
	static size_t u, ln;
	size_t e;
	ssize_t d = 0, m = 0;
	char *b = NULL, *new_b = NULL, *t;

	b = *poin;
	if (b && len)
		m = *len;
	if (u == ln)
		u = ln = 0;

	d = read_buff(inf, buff, &ln);
	if (d == -1 || (d == 0 && ln == 0))
		return (-1);

	t = _strchar(buff + u, '\n');
	e = t ? 1 + (unsigned int)(t - buff) : ln;
	new_b = _reloc(b, m, m ? m + e : e + 1);
	if (!new_b) /* MALLOC FAILURE! */
		return (b ? free(b), -1 : -1);

	if (m)
		_sncat(new_b, buff + u, e - u);
	else
		_sncpy(new_b, buff + u, e - u + 1);

	m += e - u;
	u = e;
	b = new_b;

	if (len)
		*len = m;
	*poin = b;
	return (m);
}

/**
 * signhandler - blocks ctrl-C
 * @sig_numb: the signal number
 *
 * Return: void
 */
void signhandler(__attribute__((unused))int sig_numb)
{
	_puuts("\n");
	_puuts("$ ");
	_ptchr(BUF_FLUSH);
}
