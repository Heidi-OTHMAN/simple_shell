#include "myshell.h"

/**
 * _eptchr - writes the character c to stderr
 * @m: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eptchr(char m)
{
	static int u;
	static char buff[WRITE_BUF_SIZE];

	if (m == BUF_FLUSH || u >= WRITE_BUF_SIZE)
	{
		write(2, buff, u);
		u = 0;
	}
	if (m != BUF_FLUSH)
		buff[u++] = m;
	return (1);
}

/**
 * _ptfd - writes the character c to given fd
 * @m: The character to print
 * @fdes: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _ptfd(char m, int fdes)
{
	static int u;
	static char buff[WRITE_BUF_SIZE];

	if (m == BUF_FLUSH || u >= WRITE_BUF_SIZE)
	{
		write(fdes, buff, u);
		u = 0;
	}
	if (m != BUF_FLUSH)
		buff[u++] = m;
	return (1);
}

/**
 *_ept - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void _ept(char *string)
{
	int u = 0;

	if (!string)
		return;
	while (string[u] != '\0')
	{
		_eptchr(string[u]);
		u++;
	}
}

/**
 *_ptsfd - prints an input string
 * @string: the string to be printed
 * @fdes: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _ptsfd(char *string, int fdes)
{
	int u = 0;

	if (!string)
		return (0);
	while (*string)
	{
		u += _ptfd(*string++, fdes);
	}
	return (u);
}
