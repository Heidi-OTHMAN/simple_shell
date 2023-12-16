#include "myshell.h"

/**
 * dou_chars - duplicates characters
 * @pthstr: the PATH string
 * @strt: starting index
 * @stp: stopping index
 *
 * Return: pointer to new buffer
 */
char *dou_chars(char *pthstr, int strt, int stp)
{
	static char buff[1024];
	int u = 0, e = 0;

	for (e = 0, u = strt; u < stp; u++)
		if (pthstr[u] != ':')
			buff[e++] = pthstr[u];
	buff[e] = 0;
	return (buff);
}

/**
 * a_cmd - determines if a file is an executable command
 * @inf: the info struct
 * @paath: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int a_cmd(info_t *inf, char *paath)
{
	struct stat st;

	(void)inf;
	if (!paath || stat(paath, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * fn_paath - finds this cmd in the PATH string
 * @inf: the info struct
 * @pthstr: the PATH string
 * @cmmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *fn_paath(info_t *inf, char *pthstr, char *cmmd)
{
	int u = 0, cur_pos = 0;
	char *paath;

	if (!pthstr)
		return (NULL);
	if ((_slen(cmmd) > 2) && start_with(cmmd, "./"))
	{
		if (a_cmd(inf, cmmd))
			return (cmmd);
	}
	while (1)
	{
		if (!pthstr[u] || pthstr[u] == ':')
		{
			paath = dou_chars(pthstr, cur_pos, u);
			if (!*paath)
				_scat(paath, cmmd);
			else
			{
				_scat(paath, "/");
				_scat(paath, cmmd);
			}
			if (a_cmd(inf, paath))
				return (paath);
			if (!pthstr[u])
				break;
			cur_pos = u;
		}
		u++;
	}
	return (NULL);
}
