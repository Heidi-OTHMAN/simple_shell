#include "myshell.h"

/**
 **_sncat - concatenates two strings
 *@destin: the first string
 *@sour: the second string
 *@w: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_sncat(char *destin, char *sour, int w)
{
	int u, t;
	char *r = destin;

	u = 0;
	t = 0;
	while (destin[u] != '\0')
		u++;
	while (sour[t] != '\0' && t < w)
	{
		destin[u] = sour[t];
		u++;
		t++;
	}
	if (t < w)
		destin[u] = '\0';
	return (r);
}

/**
 **_sncpy - copies a string
 *@destin: the destination string to be copied to
 *@sour: the source string
 *@w: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_sncpy(char *destin, char *sour, int w)
{
	int u, t;
	char *r = destin;

	u = 0;
	while (sour[u] != '\0' && u < w - 1)
	{
		destin[u] = sour[u];
		u++;
	}
	if (u < w)
	{
		t = u;
		while (t < w)
		{
			destin[t] = '\0';
			t++;
		}
	}
	return (r);
}


/**
 **_strchar - locates a character in a string
 *@str: the string to be parsed
 *@m: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchar(char *str, char m)
{
	do {
		if (*str == m)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
