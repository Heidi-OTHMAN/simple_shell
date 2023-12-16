#include "myshell.h"

/**
 * print_err - prints an error message
 * @inf: the parameter & return info struct
 * @est: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_err(info_t *inf, char *est)
{
	_ept(inf->fnm);
	_ept(": ");
	prnt_d(inf->line_cnt, STDERR_FILENO);
	_ept(": ");
	_ept(inf->arggv[0]);
	_ept(": ");
	_ept(est);
}

/**
 * prnt_d - function prints a decimal (integer) number (base 10)
 * @inpt: the input
 * @fdes: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int prnt_d(int inpt, int fdes)
{
	int (*__ptchr)(char) = _ptchr;
	int u, cnt = 0;
	unsigned int _abs_, curr;

	if (fdes == STDERR_FILENO)
		__ptchr = _eptchr;
	if (inpt < 0)
	{
		_abs_ = -inpt;
		__ptchr('-');
		cnt++;
	}
	else
		_abs_ = inpt;
	curr = _abs_;
	for (u = 1000000000; u > 1; u /= 10)
	{
		if (_abs_ / u)
		{
			__ptchr('0' + curr / u);
			cnt++;
		}
		curr %= u;
	}
	__ptchr('0' + curr);
	cnt++;

	return (cnt);
}

/**
 * _erati - converts a string to an integer
 * @a: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erati(char *a)
{
	int u = 0;
	unsigned long int res = 0;

	if (*a == '+')
		a++;  /* TODO: why does this make main return 255? */
	for (u = 0;  a[u] != '\0'; u++)
	{
		if (a[u] >= '0' && a[u] <= '9')
		{
			res *= 10;
			res += (a[u] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * conv_number - converter function, a clone of itoa
 * @numb: number
 * @bas: base
 * @flgs: argument flags
 *
 * Return: string
 */
char *conv_number(long int numb, int bas, int flgs)
{
	static char *arr;
	static char buffr[50];
	char sig = 0;
	char *poin;
	unsigned long t = numb;

	if (!(flgs & CONVERT_UNSIGNED) && numb < 0)
	{
		t = -numb;
		sig = '-';

	}
	arr = flgs & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	poin = &buffr[49];
	*poin = '\0';

	do	{
		*--poin = arr[t % bas];
		t /= bas;
	} while (t != 0);

	if (sig)
		*--poin = sig;
	return (poin);
}

/**
 * rm_comments - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0;
 */
void rm_comments(char *buff)
{
	int u;

	for (u = 0; buff[u] != '\0'; u++)
		if (buff[u] == '#' && (!u || buff[u - 1] == ' '))
		{
			buff[u] = '\0';
			break;
		}
}
