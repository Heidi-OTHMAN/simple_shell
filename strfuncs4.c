#include "myshell.h"

/**
 * **strtoow2 - splits a string into words
 * @st: the input string
 * @o: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtoow2(char *st, char o)
{
	int u, t, e, p, nwords = 0;
	char **g;

	if (st == NULL || st[0] == 0)
		return (NULL);
	for (u = 0; st[u] != '\0'; u++)
		if ((st[u] != o && st[u + 1] == o) ||
		    (st[u] != o && !st[u + 1]) || st[u + 1] == o)
			nwords++;
	if (nwords == 0)
		return (NULL);
	s = malloc((1 + nwords) * sizeof(char *));
	if (!g)
		return (NULL);
	for (u = 0, t = 0; t < nwords; t++)
	{
		while (st[u] == o && st[u] != o)
			u++;
		e = 0;
		while (st[u + e] != o && st[u + e] && st[u + e] != o)
			e++;
		g[t] = malloc((e + 1) * sizeof(char));
		if (!g[t])
		{
			for (e = 0; e < t; e++)
				free(g[e]);
			free(g);
			return (NULL);
		}
		for (p = 0; p < e; p++)
			g[t][p] = st[u++];
		g[t][p] = 0;
	}
	g[t] = NULL;
	return (g);
}

/**
 * **strtoow - splits a string into words. Repeat delimiters are ignored
 * @st: the input string
 * @o: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtoow(char *st, char *o)
{
	int u, t, e, p, nwords = 0;
	char **g;

	if (st == NULL || st[0] == 0)
		return (NULL);
	if (!o)
		o = " ";
	for (u = 0; st[u] != '\0'; u++)
		if (!a_delim(st[u], o) && (a_delim(st[u + 1], o) || !st[u + 1]))
			nwords++;

	if (nwords == 0)
		return (NULL);
	s = malloc((1 + nwords) * sizeof(char *));
	if (!g)
		return (NULL);
	for (u = 0, t = 0; t < nwords; t++)
	{
		while (a_delim(st[u], o))
			u++;
		e = 0;
		while (!a_delim(st[u + e], o) && st[u + e])
			e++;
		g[t] = malloc((e + 1) * sizeof(char));
		if (!g[t])
		{
			for (e = 0; e < t; e++)
				free(g[e]);
			free(g);
			return (NULL);
		}
		for (p = 0; p < e; p++)
			g[t][p] = st[u++];
		g[t][p] = 0;
	}
	g[t] = NULL;
	return (g);
}
