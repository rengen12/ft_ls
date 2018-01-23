/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 20:04:00 by amichak           #+#    #+#             */
/*   Updated: 2017/12/26 20:04:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_printf.h"

size_t	print_num(t_fs *fs, va_list ap)
{
	ssize_t	var;
	size_t	i;

	i = 0;
	var = va_arg(ap, ssize_t);
	usemodifs(fs, &var);
	if (var < 0)
		fs->nf = 1;
	if (!fs->prec && !var)
		i += padding(fs, 0);
	else
	{
		i += padding(fs, ft_wordlen(var));
		i += ft_putnbr_prntf(var, fs);
	}
	return (i);
}

size_t	print_unsig(t_fs *fs, va_list ap)
{
	size_t	i;
	char	*systemstr;
	char	*str;
	size_t	var;

	i = 0;
	var = va_arg(ap, size_t);
	usemodifu(fs, &var);
	i += handle_sharp(var, fs);
	if ((systemstr = NULL) == NULL && fs->ch == 'u')
		systemstr = "0123456789";
	else if (fs->ch == 'X')
		systemstr = "0123456789ABCDEF";
	else if (fs->ch == 'x' || fs->ch == 'p')
		systemstr = "0123456789abcdef";
	else if (fs->ch == 'o')
		systemstr = "01234567";
	else if (fs->ch == 'b')
		systemstr = "01";
	str = ft_convert_base_printf(var, systemstr, fs);
	i += padding(fs, ft_strlen_printf(str) + i);
	i += ft_putstr_pf(str, fs);
	ft_strdel(&str);
	return (i);
}
