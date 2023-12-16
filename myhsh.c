#include "myshell.h"

/**
 * fn_bultin - finds a builtin command
 * @inf: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int fn_bultin(info_t *inf)
{
	int u, bult_in_retu = -1;
	builtin_table builtintbl[] = {
		{"exit", _ourexit},
		{"env", _oenv},
		{"help", _ourhelp},
		{"history", _ourhistory},
		{"setenv", _osetenv},
		{"unsetenv", _ounsetenv},
		{"cd", _ourcd},
		{"alias", _ouralas},
		{NULL, NULL}
	};

	for (u = 0; builtintbl[u].type; u++)
		if (_strcom(inf->arggv[0], builtintbl[u].type) == 0)
		{
			inf->line_cnt++;
			bult_in_retu = builtintbl[u].func(inf);
			break;
		}
	return (bult_in_retu);
}

/**
 * fn_cmd - finds a command in PATH
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void fn_cmd(info_t *inf)
{
	char *paath = NULL;
	int u, m;

	inf->paath = inf->arggv[0];
	if (inf->linecnt_flag == 1)
	{
		inf->line_cnt++;
		inf->linecnt_flag = 0;
	}
	for (u = 0, m = 0; inf->argg[u]; u++)
		if (!a_delim(inf->argg[u], " \t\n"))
			m++;
	if (!m)
		return;

	paath = fn_paath(inf, _genv(inf, "PATH="), inf->arggv[0]);
	if (paath)
	{
		inf->paath = paath;
		foork_cmd(inf);
	}
	else
	{
		if ((inactive(inf) || _genv(inf, "PATH=")
			|| inf->arggv[0][0] == '/') && a_cmd(inf, inf->arggv[0]))
			foork_cmd(inf);
		else if (*(inf->argg) != '\n')
		{
			inf->stats = 127;
			print_err(inf, "not found\n");
		}
	}
}

/**
 * hshhh - main shell loop
 * @inf: the parameter & return info struct
 * @avec: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hshhh(info_t *inf, char **avec)
{
	ssize_t d = 0;
	int bultin_retu = 0;

	while (d != -1 && bultin_retu != -2)
	{
		clr_info(inf);
		if (inactive(inf))
			_puuts("$ ");
		_eptchr(BUF_FLUSH);
		d = get_inpt(inf);
		if (d != -1)
		{
			s_info(inf, avec);
			bultin_retu = fn_bultin(inf);
			if (bultin_retu == -1)
				fn_cmd(inf);
		}
		else if (inactive(inf))
			_ptchr('\n');
		fr_info(inf, 0);
	}
	write_his(inf);
	fr_info(inf, 1);
	if (!inactive(inf) && inf->stats)
		exit(inf->stats);
	if (bultin_retu == -2)
	{
		if (inf->err_numb == -1)
			exit(inf->stats);
		exit(inf->err_numb);
	}
	return (bultin_retu);
}

/**
 * foork_cmd - forks a an exec thread to run cmd
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void foork_cmd(info_t *inf)
{
	pid_t ch_pid;

	ch_pid = fork();
	if (ch_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (ch_pid == 0)
	{
		if (execve(inf->paath, inf->arggv, get_enviro(inf)) == -1)
		{
			fr_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(inf->stats));
		if (WIFEXITED(inf->stats))
		{
			inf->stats = WEXITSTATUS(inf->stats);
			if (inf->stats == 126)
				print_err(inf, "Permission denied\n");
		}
	}
}
