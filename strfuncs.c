#include "myshell.h"

/**
 * _strcom - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @str2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcom(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * start_with - checks if needle starts with haystack
 * @hystck: string to search
 * @nedl: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *start_with(const char *hystck, const char *nedl)
{
	while (*nedl)
		if (*nedl++ != *hystck++)
			return (NULL);
	return ((char *)hystck);
}

/**
 * _slen - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int _slen(char *str)
{
	int u = 0;

	if (!str)
		return (0);

	while (*str++)
		u++;
	return (u);
}

/**
 * _scat - concatenates two strings
 * @destin: the destination buffer
 * @sour: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_scat(char *destin, char *sour)
{
	char *retu = destin;

	while (*destin)
		destin++;
	while (*sour)
		*destin++ = *sour++;
	*destin = *sour;
	return (retu);
}
