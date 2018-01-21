#include <stdio.h>
#include "ft_ls.h"

void	handle_flags(t_fl *fl, int ac, char **av)
{
	int i;

	i = 1;
	fl->a = 0;
	fl->br = 0;
	fl->l = 0;
	fl->r = 0;
	fl->t = 0;
	if (ac > 1)
	{
		while (i < ac)
		{
			if (av[i][0] == '-')
				
			i++;
		}
	}
}

int		main(int ac, char **av)
{
	t_fl	fl;

	handle_flags(&fl, ac, av);

	return (0);
}