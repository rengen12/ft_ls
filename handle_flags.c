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
	int i;

	i = 0;
	*fl = (t_flags){0, 0, 0, 0, 0, 0, 0};
	fl->ac = ac;
	while (++i < ac && av[i][0] == '-')
		while (*++av[i])
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
			else
				pr_usage(*av[i]);
	fl->st = (i < ac) ? i : 0;
}
