#include "myshell.h"


/**
 * _ourcd - changes the current directory of the process
 * @inf: Structure contain potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _ourcd(info_t *inf)
{
	char *str, *direc, buf[1024];
	int chdir_return;

	str = getcwd(buf, 1024);
	if (!str)
		_puuts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->arggv[1])
	{
		direc = _genv(inf, "HOME=");
		if (!direc)
			chdir_return = /* TODO: what should this be? */
				chdir((direc = _genv(inf, "PWD=")) ? direc : "/");
		else
			chdir_return = chdir(direc);
	}
	else if (_strcom(inf->arggv[1], "-") == 0)
	{
		if (!_genv(inf, "OLDPWD="))
		{
			_puuts(str);
			_ptchr('\n');
			return (1);
		}
		_puuts(_genv(inf, "OLDPWD=")), _ptchr('\n');
		chdir_return = /* TODO: what should this be? */
			chdir((direc = _genv(inf, "OLDPWD=")) ? direc : "/");
	}
	else
		chdir_return = chdir(inf->arggv[1]);
	if (chdir_return == -1)
	{
		print_err(inf, "can't cd to ");
		_ept(inf->arggv[1]), _eptchr('\n');
	}
	else
	{
		_senv(inf, "OLDPWD", _genv(inf, "PWD="));
		_senv(inf, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * _ourexit - exits the shell
 * @inf: Structure contain potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if inf.argv[0] != "exit"
 */
int _ourexit(info_t *inf)
{
	int extchck;

	if (inf->arggv[1])  /* If there is an exit arguement */
	{
		extchck = _erati(inf->arggv[1]);
		if (extchck == -1)
		{
			inf->stats = 2;
			print_err(inf, "Illegal number: ");
			_ept(inf->arggv[1]);
			_eptchr('\n');
			return (1);
		}
		inf->err_numb = _erati(inf->arggv[1]);
		return (-2);
	}
	inf->err_numb = -1;
	return (-2);
}

/**
 * _ourhelp - changes the current directory of the process
 * @inf: Structure contain potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _ourhelp(info_t *inf)
{
	char **arg_arr;

	arg_arr = inf->arggv;
	_puuts("help call works. Function not yet implemented \n");
	if (0)
		_puuts(*arg_arr); /* temp att_unused workaround */
	return (0);
}
