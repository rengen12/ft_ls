/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 17:13:03 by amichak           #+#    #+#             */
/*   Updated: 2018/02/01 17:13:06 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	pr_usage(char c)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(c);
	ft_putchar('\n');
	ft_putendl("usage: ls [-Ralrt] [file ...]");
	exit(1);
}

void		handle_flags(t_flags *fl, int ac, char **av)
{
	int	i;

	i = 0;
	*fl = (t_flags){0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	fl->ac = ac;
	while (++i < ac && av[i][0] == '-' && av[i][1])
		while (*++av[i])
			if (*av[i] == 'a')
				fl->a = 1;
            else if (*av[i] == 'A')
                fl->ba = 1;
            else if (*av[i] == 'f')
                fl->f = 1;
			else if (*av[i] == 'R')
				fl->br = 1;
			else if (*av[i] == 'l')
			{
				fl->l = 1;
				fl->o = 0;
			}
			else if (*av[i] == 'r')
				fl->r = 1;
			else if (*av[i] == 't')
				fl->t = 1;
			else if (*av[i] == '1')
			{
				fl->o = 1;
				fl->l = 0;
			}
			/*else if (*av[i] == '-')
			{
				fl->st = (i < ac) ? i + 1 : 0;
				return ;
			}*/
			else
				pr_usage(*av[i]);
	fl->st = (i < ac) ? i : 0;
}
