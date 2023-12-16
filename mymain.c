#include "myshell.h"

/**
 * main - entry point
 * @agc: arg count
 * @avec: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int agc, char **avec)
{
	info_t inf[] = { INFO_INIT };
	int fdes = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fdes)
		: "r" (fdes));

	if (agc == 2)
	{
		fdes = open(avec[1], O_RDONLY);
		if (fdes == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_ept(av[0]);
				_ept(": 0: Can't open ");
				_ept(av[1]);
				_eptchr('\n');
				_eptchr(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->redfd = fdes;
	}
	pop_env_list(inf);
	read_his(inf);
	hshhh(inf, avec);
	return (EXIT_SUCCESS);
}
