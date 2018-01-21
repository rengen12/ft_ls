/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 20:15:00 by amichak           #+#    #+#             */
/*   Updated: 2017/12/26 20:15:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_printf.h"

static void	calc_pad(t_fs *fs)
{
	if ((fs->zero && fs->prec_exist && ft_strchr("oxXubdfpeE", fs->ch)) || \
		(fs->zero && fs->minus))
		fs->zero = 0;
	else if (fs->zero)
		fs->prec = ((fs->plus) || (fs->nf && !fs->plus) || fs->space) ? \
					fs->width - 1 : fs->width;
}

size_t		padding(t_fs *fs, int wordlen)
{
	size_t i;

	i = 0;
	calc_pad(fs);
	while (fs->width > wordlen + (fs->nf || fs->plus || fs->space) && \
			!fs->minus && !fs->zero && fs->prec + (fs->nf || \
			fs->plus || fs->space) < fs->width)
	{
		i += ft_putchar(' ');
		fs->width--;
	}
	if (!ft_strchr("feEd%", fs->ch) || (fs->ch == '%' && fs->zero))
		while (fs->prec > wordlen && (((fs->ch == 'c' || fs->ch == 'C') \
				&& fs->zero) || (fs->ch != 'c' && fs->ch != 'C')))
		{
			i += ft_putchar('0');
			fs->prec--;
		}
	return (i);
}

size_t		padding_after(t_fs *fs, int wordlen)
{
	size_t i;

	i = 0;
	while (fs->width > wordlen && fs->minus)
	{
		i += ft_putchar(' ');
		fs->width--;
	}
	return (i);
}

size_t		padding_afsign(t_fs *fs, int wordlen)
{
	size_t i;

	i = 0;
	while (fs->prec > wordlen && !ft_strchr("feE", fs->ch))
	{
		i += ft_putchar('0');
		fs->prec--;
	}
	return (i);
}

size_t		padding_str(t_fs *fs, int wordlen)
{
	size_t i;

	i = 0;
	if (((fs->zero && fs->minus)) && fs->ch != 'S')
		fs->zero = 0;
	else if (fs->zero)
		fs->prec = fs->width;
	while (fs->width > wordlen && !fs->minus && !fs->zero)
	{
		i += ft_putchar(' ');
		fs->width--;
	}
	while (fs->prec > wordlen && fs->zero)
	{
		i += ft_putchar('0');
		fs->prec--;
	}
	return (i);
}
