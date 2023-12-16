#include "myshell.h"

/**
 * write_his - creates a file, or appends to an existing file
 * @inf: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_his(info_t *inf)
{
	ssize_t fdes;
	char *filenme = get_his_file(inf);
	list_t *nod = NULL;

	if (!filenme)
		return (-1);

	fdes = open(filenme, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenme);
	if (fdes == -1)
		return (-1);
	for (nod = inf->his; nod; nod = nod->nxt)
	{
		_ptsfd(nod->string, fdes);
		_ptfd('\n', fdes);
	}
	_ptfd(BUF_FLUSH, fdes);
	close(fdes);
	return (1);
}

/**
 * read_his - reads history from file
 * @inf: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_his(info_t *inf)
{
	int u, la = 0, linecnt = 0;
	ssize_t fdes, rdln, fisize = 0;
	struct stat st;
	char *buff = NULL, *filenme = get_his_file(inf);

	if (!filenme)
		return (0);

	fdes = open(filenme, O_RDONLY);
	free(filenme);
	if (fdes == -1)
		return (0);
	if (!fstat(fdes, &st))
		fisize = st.st_size;
	if (fisize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fisize + 1));
	if (!buff)
		return (0);
	rdln = read(fdes, buff, fisize);
	buff[fisize] = 0;
	if (rdln <= 0)
		return (free(buff), 0);
	close(fdes);
	for (u = 0; u < fisize; u++)
		if (buff[u] == '\n')
		{
			buff[u] = 0;
			build_his_lst(inf, buff + la, linecnt++);
			la = u + 1;
		}
	if (la != u)
		build_his_lst(inf, buff + la, linecnt++);
	free(buff);
	inf->histcnt = linecnt;
	while (inf->histcnt-- >= HIST_MAX)
		del_nod_at_inx(&(inf->his), 0);
	renum_history(inf);
	return (inf->histcnt);
}

/**
 * get_his_file - gets the history file
 * @inf: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_his_file(info_t *inf)
{
	char *buff, *direc;

	direc = _genv(inf, "HOME=");
	if (!direc)
		return (NULL);
	buff = malloc(sizeof(char) * (_slen(direc) + _slen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_scpy(buff, direc);
	_scat(buff, "/");
	_scat(buff, HIST_FILE);
	return (buff);
}

/**
 * build_his_lst - adds entry to a history linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @linecnt: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_his_lst(info_t *inf, char *buff, int linecnt)
{
	list_t *nod = NULL;

	if (inf->his)
		nod = inf->his;
	ad_nod_end(&nod, buff, linecnt);

	if (!inf->his)
		inf->his = nod;
	return (0);
}

/**
 * renum_history - renumbers the history linked list after changes
 * @inf: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renum_history(info_t *inf)
{
	list_t *nod = inf->his;
	int u = 0;

	while (nod)
	{
		nod->numb = u++;
		nod = nod->nxt;
	}
	return (inf->histcnt = u);
}
