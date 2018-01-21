/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 19:29:00 by amichak           #+#    #+#             */
/*   Updated: 2017/12/26 19:29:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_printf.h"

static size_t	print_sym_e(t_fs *fs, size_t i_e)
{
	size_t	i;

	i = 0;
	if (fs->ch == 'e' || fs->ch == 'E')
	{
		i += ft_putchar(fs->ch);
		i += ft_putchar('+');
		if (i_e >= 10)
			i += ft_putnbr_prntf(i_e, fs);
		else
		{
			i += ft_putnbr_prntf(0, fs);
			i += ft_putnbr_prntf(i_e, fs);
		}
	}
	return (i);
}

static size_t	prepare_float(t_fs *fs, long double *var, va_list ap, \
	size_t *i_e)
{
	size_t	i;

	i = 0;
	*i_e = 0;
	if (fs->l)
		*var = va_arg(ap, long double);
	else
		*var = va_arg(ap, double);
	if (*var < 0)
	{
		*var *= -1;
		fs->nf = 1;
	}
	if (fs->prec == -1)
		fs->prec = 6;
	if (fs->ch == 'e' || fs->ch == 'E')
		while ((size_t)*var >= 10)
		{
			(*i_e)++;
			*var /= 10;
		}
	i += padding(fs, ft_wordlen((size_t)*var) + (fs->prec > 0) + fs->prec + \
			((fs->ch == 'e' || fs->ch == 'E') ? 4 : 0));
	return (i);
}

size_t			print_float(t_fs *fs, va_list ap)
{
	size_t		i;
	size_t		i_e;
	long double	var;

	i = prepare_float(fs, &var, ap, &i_e);
	i += ft_putnbr_prntf((size_t)var, fs);
	fs->nf = 0;
	if (fs->prec > 0)
		i += ft_putchar('.');
	while (fs->prec-- > 0)
	{
		var -= (size_t)var;
		var += 0.000000000001;
		var *= 10;
		if ((fs->prec == 0) && ((size_t)(var * 10) % 10) >= 5)
			var++;
		i += ft_putnbr_prntf((size_t)var, fs);
	}
	i += print_sym_e(fs, i_e);
	return (i);
}
