#include "myshell.h"

/**
 * _strup - duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strup(const char *string)
{
	int leng = 0;
	char *retu;

	if (string == NULL)
		return (NULL);
	while (*string++)
		leng++;
	retu = malloc(sizeof(char) * (leng + 1));
	if (!retu)
		return (NULL);
	for (leng++; leng--;)
		retu[leng] = *--string;
	return (retu);
}

/**
 *_puuts - prints an input string
 *@string: the string to be printed
 *
 * Return: Nothing
 */
void _puuts(char *string)
{
	int u = 0;

	if (!string)
		return;
	while (string[u] != '\0')
	{
		_ptchr(string[u]);
		u++;
	}
}

/**
 * _scpy - copies a string
 * @destin: the destination
 * @sour: the source
 *
 * Return: pointer to destination
 */
char *_scpy(char *destin, char *sour)
{
	int u = 0;

	if (destin == sour || sour == 0)
		return (destin);
	while (sour[u])
	{
		destin[u] = sour[u];
		u++;
	}
	destin[u] = 0;
	return (destin);
}

/**
 * _ptchr - writes the character c to stdout
 * @m: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _ptchr(char m)
{
	static int u;
	static char buff[WRITE_BUF_SIZE];

	if (m == BUF_FLUSH || u >= WRITE_BUF_SIZE)
	{
		write(1, buff, u);
		u = 0;
	}
	if (m != BUF_FLUSH)
		buff[u++] = m;
	return (1);
}
