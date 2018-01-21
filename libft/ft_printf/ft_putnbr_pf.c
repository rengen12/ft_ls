/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 21:02:46 by amichak           #+#    #+#             */
/*   Updated: 2017/10/25 21:22:18 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_printf.h"

static size_t	ft_putnbr_rec(size_t n, size_t i)
{
	if (n >= 10)
		i = ft_putnbr_rec(n / 10, i);
	i += ft_putchar((char)((n % 10) + '0'));
	return (i);
}

size_t			ft_putnbr_prntf(ssize_t nb, t_fs *fs)
{
	size_t	i;
	size_t	n;

	i = 0;
	if (nb < 0)
		n = -nb;
	else
		n = nb;
	if (fs)
	{
		if (!fs->nf && !fs->plus && fs->space)
			i += ft_putchar(' ');
		else if (!fs->nf && fs->plus)
			i += ft_putchar('+');
		else if (fs->nf)
			i += ft_putchar('-');
		i += padding_afsign(fs, ft_wordlen(nb));
	}
	i += ft_putnbr_rec(n, 0);
	return (i);
}
