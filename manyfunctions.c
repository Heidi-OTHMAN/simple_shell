#include "myshell.h"

/**
 * a_delim - checks if character is a delimeter
 * @m: the char to check
 * @delm: the delimeter string
 * Return: 1 if true, 0 if false
 */
int a_delim(char m, char *delm)
{
	while (*delm)
		if (*delm++ == m)
			return (1);
	return (0);
}

/**
 *_analpha - checks for alphabetic character
 *@m: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _analpha(int m)
{
	if ((m >= 'a' && m <= 'z') || (m >= 'A' && m <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * inactive - returns true if shell is interactive mode
 * @inf: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int inactive(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->redfd <= 2);
}

/**
 *_ati - converts a string to an integer
 *@a: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _ati(char *a)
{
	int u, sig = 1, flg = 0, outp;
	unsigned int res = 0;

	for (u = 0;  a[u] != '\0' && flg != 2; u++)
	{
		if (a[u] == '-')
			sig *= -1;

		if (a[u] >= '0' && a[u] <= '9')
		{
			flg = 1;
			res *= 10;
			res += (a[u] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (sig == -1)
		outp = -res;
	else
		outp = res;

	return (outp);
}
