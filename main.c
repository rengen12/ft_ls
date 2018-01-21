#include <stdio.h>
#include "ft_ls.h"

void	handle_flags(t_fl *fl, int ac, char **av)
{
	int i;

	i = 0;
	fl->a = 0;
	fl->br = 0;
	fl->l = 0;
	fl->r = 0;
	fl->t = 0;
	if (ac > 1)
	{
		while (++i < ac)
		{
			if (av[i][0] == '-')
			{
				while (*++av[i])
				{
					if (*av[i] == 'a')
						fl->a = 1;
					else if (*av[i] == 'R')
						fl->br = 1;
					else if (*av[i] == 'l')
						fl->l = 1;
					else if (*av[i] == 'r')
						fl->r = 1;
					else if (*av[i] == 't')
						fl->t = 1;
				}
			}
			else
				continue ;
		}
	}
}

int		main(int ac, char **av)
{
	t_fl	fl;

	handle_flags(&fl, ac, av);

	return (0);
}