#include "myshell.h"

/**
 * s_info - initializes info_t struct
 * @inf: struct address
 * @avec: argument vector
 */
void s_info(info_t *inf, char **avec)
{
	int u = 0;

	inf->fnm = avec[0];
	if (inf->argg)
	{
		inf->arggv = strtoow(inf->argg, " \t");
		if (!inf->arggv)
		{

			inf->arggv = malloc(sizeof(char *) * 2);
			if (inf->arggv)
			{
				inf->arggv[0] = _strup(inf->argg);
				inf->arggv[1] = NULL;
			}
		}
		for (u = 0; inf->arggv && inf->arggv[u]; u++)
			;
		inf->arc = u;

		rep_alias(inf);
		rep_vars(inf);
	}
}

/**
 * clr_info - initializes info_t struct
 * @inf: struct address
 */
void clr_info(info_t *inf)
{
	inf->argg = NULL;
	inf->arggv = NULL;
	inf->paath = NULL;
	inf->arc = 0;
}

/**
 * fr_info - frees info_t struct fields
 * @inf: struct address
 * @al: true if freeing all fields
 */
void fr_info(info_t *inf, int al)
{
	struct list_t l;

	l = malloc(sizeof(struct list_t));

	ffr(inf->arggv);
	inf->arggv = NULL;
	inf->paath = NULL;
	if (al)
	{
		if (!inf->cmd_buff)
			free(inf->argg);
		if (inf->enviro)
			fr_list(&(l->enviro));
		if (inf->his)
			fr_list(&(l->his));
		if (inf->alas)
			fr_list(&(l->alas));
		ffr(inf->enviroon);
			inf->enviroon = NULL;
		bfr((void **)inf->cmd_buff);
		if (inf->redfd > 2)
			close(inf->redfd);
		_ptchr(BUF_FLUSH);
	}
}
