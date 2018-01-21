/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:36:21 by amichak           #+#    #+#             */
/*   Updated: 2017/11/03 17:36:23 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_printf.h"

static void	parse_convert_base(size_t nb, char *bt, size_t c, char *r)
{
	if (nb >= c)
		parse_convert_base(nb / c, bt, c, r);
	ft_strncat_pf(r, &bt[nb % c], 1);
}

static char	*add_pre(size_t nb, char *cnvrtd, t_fs *fs)
{
	char	*pre;
	size_t	cnvl;

	cnvl = ft_strlen_printf(cnvrtd);
	pre = ft_strnew(2 + fs->prec + cnvl);
	if (!fs->zero && pre)
	{
		if ((nb && fs->ch == 'x' && fs->sh) || fs->ch == 'p')
			ft_strncat_pf(pre, "0x", 2);
		else if (nb && fs->ch == 'X' && fs->sh)
			ft_strncat_pf(pre, "0X", 2);
		else if (nb && (fs->ch == 'o' || fs->ch == 'O') && fs->sh)
			ft_strncat_pf(pre, "0", 1);
	}
	if (fs->ch == 'o' && fs->sh)
		cnvl++;
	while ((size_t)fs->prec-- > cnvl)
		ft_strncat_pf(pre, "0", 1);
	ft_strncat_pf(pre, cnvrtd, cnvl);
	ft_strdel(&cnvrtd);
	return (pre);
}

char		*ft_convert_base_printf(size_t nb, char *base_to, t_fs *fs)
{
	char	*r;
	size_t	l;
	int		mem;

	l = ft_strlen_printf(base_to);
	if (!l || (!nb && fs->ch != 'p' && (l == 16 || (l == 8 && !fs->sh))))
		return (NULL);
	mem = (fs->ch == 'b') ? 62 : 21;
	r = ft_strnew(mem);
	if (r && (fs->prec > 0 || (fs->sh && fs->ch == 'o')))
		parse_convert_base(nb, base_to, l, &(*r));
	return (add_pre(nb, r, fs));
}
