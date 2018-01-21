/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 19:01:00 by amichak           #+#    #+#             */
/*   Updated: 2017/12/26 19:01:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_printf.h"

size_t	handle_sharp(size_t nb, t_fs *fs)
{
	size_t i;

	i = 0;
	if (fs->zero)
	{
		if ((nb && fs->ch == 'x' && fs->sh) || fs->ch == 'p')
			i += ft_putstr("0x", fs);
		else if (nb && fs->ch == 'X' && fs->sh)
			i += ft_putstr("0X", fs);
		else if (nb && (fs->ch == 'o' || fs->ch == 'O') && fs->sh)
			i += ft_putstr("0", fs);
	}
	return (i);
}

void	handle_flags(t_fs *fs, char ch)
{
	if (ch == '-')
		fs->minus = 1;
	else if (ch == '+')
		fs->plus = 1;
	else if (ch == '#')
		fs->sh = 1;
	else if (ch == ' ')
		fs->space = 1;
	else if (ch == '0')
		fs->zero = 1;
}

void	handle_modif(t_fs *fs, char ch)
{
	if (ch == 'h')
		fs->h++;
	else if (ch == 'l' || ch == 'L')
		fs->l++;
	else if (ch == 'z' || ch == 'Z')
		fs->z++;
	else if (ch == 'j')
		fs->j++;
}

void	handle_str_point(va_list ap, const char **s, t_fs *fs)
{
	(*s)++;
	if (**s == '*')
	{
		fs->prec = va_arg(ap, int);
		fs->prec = (fs->prec < 0 && fs->zero) ? fs->width : fs->prec;
		(*s)++;
	}
	else
	{
		fs->prec = ft_atoi_printf(s);
		fs->prec = (fs->prec > 0) ? fs->prec : 0;
	}
	fs->prec_exist = 1;
}

size_t	handle_str_fs(va_list ap, const char **s, t_fs *fs)
{
	while (**s == '-' || **s == '+' || **s == '#' || **s == ' ' || \
			**s == '0')
		handle_flags(fs, *(*s)++);
	while ((**s >= '0' && **s <= '9') || **s == '*')
		if (**s == '*')
		{
			fs->width = va_arg(ap, int);
			if (fs->width < 0)
				fs->minus = 1;
			fs->width = ABS(fs->width);
			(*s)++;
		}
		else
			fs->width = ft_atoi_printf(s);
	while (**s == '.')
		handle_str_point(ap, s, fs);
	while (**s == 'h' || **s == 'l' || **s == 'L' || **s == 'j' || **s == 'z')
		handle_modif(fs, *(*s)++);
	while (**s == '-' || **s == '+' || **s == '#' || **s == ' ' || **s == '0' \
			|| **s == '\'')
		handle_flags(fs, *(*s)++);
	if (!**s)
		return (0);
	read_conv_mod(fs, s);
	return (print_str_fs(fs, ap));
}
