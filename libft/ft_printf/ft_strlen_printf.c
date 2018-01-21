/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 17:05:11 by amichak           #+#    #+#             */
/*   Updated: 2017/11/17 17:05:17 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_printf.h"

int				ft_wordlen(ssize_t var)
{
	int		i;

	i = 0;
	while (var)
	{
		var /= 10;
		i++;
	}
	if (!i)
		i = 1;
	return (i);
}

size_t			ft_strlen_printf(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

static size_t	charlen(int c)
{
	if (c <= 127 && MB_CUR_MAX > 1)
		return (1);
	else if (c <= 255 && MB_CUR_MAX == 1)
		return (1);
	else if (c <= 2047)
		return (2);
	else if (c <= 65535)
		return (3);
	else if (c <= 2097151)
		return (4);
	else
		return (0);
}

size_t			ft_strlen_u(char *s, t_fs *fs)
{
	int		num;
	size_t	i;
	size_t	chlen;

	i = 0;
	if (s)
		while (*s || *(s + 1) || *(s + 2) || *(s + 3))
		{
			num = 0;
			num += (unsigned char)*s;
			num += ((int)((unsigned char)*(s + 1))) << 8;
			num += ((int)((unsigned char)*(s + 2))) << 16;
			num += ((int)((unsigned char)*(s + 3))) << 24;
			chlen = charlen(num);
			if (fs->prec_exist && i + chlen > (size_t)fs->prec)
				return (i);
			if (!chlen)
				break ;
			i += chlen;
			s += 4;
		}
	return (i);
}
