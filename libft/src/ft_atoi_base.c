/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:36:14 by amichak           #+#    #+#             */
/*   Updated: 2017/11/03 17:36:16 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			check_base(char *b, char *c)
{
	if (b && c)
		while (*c && *b && *c++ == *b++)
			if (*b == '\0')
				return (1);
	return (0);
}

static int			ind(char c, const char *b)
{
	int				counter;

	counter = 0;
	while (*b && *b != c)
	{
		counter++;
		b++;
	}
	return (counter);
}

static long long	atoi_parse(char *s, char *b, int cb)
{
	int				sign;
	long long		r;

	sign = 1;
	r = 0;
	while (*s == ' ' || *s == '\n' || *s == '\t' || *s == '\f' || \
		*s == '\v' || *s == '\r')
		s++;
	sign = *s == '-';
	if (*s == '+' || *s == '-')
		s++;
	while (ind(*s, b) < cb)
		r = r * cb + ind(*s++, b);
	return (sign ? -r : r);
}

long long			ft_atoi_base(char *s, char *base)
{
	int				cb;

	if (!s || !base)
		return (0);
	if (!check_base(base, "0123456789ABCDEF"))
		return (0);
	cb = ft_strlen(base);
	if (cb < 2)
		return (0);
	return (atoi_parse(s, base, cb));
}
