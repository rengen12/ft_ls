/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:43:39 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:43:40 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	qwords(char const *s, char c)
{
	size_t	qw;

	qw = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c && *s)
		{
			qw++;
			while (*s != c && *s)
				s++;
		}
	}
	return (qw);
}

static char		**fr_all(char **s, size_t index)
{
	size_t	i;

	i = 0;
	while (i < index && s[i])
		ft_strdel(&s[i++]);
	ft_strdel(s);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**r;
	size_t	i;
	size_t	qw;
	size_t	my_len;
	char	*nx_ch;

	r = NULL;
	i = 0;
	qw = s ? qwords(s, c) : 0;
	if (!s || !(r = (char **)malloc(sizeof(char *) * (qw + 1))))
		return (NULL);
	while (i < qw && *s)
	{
		while (*s == c && *s)
			s++;
		nx_ch = ft_strchr(s, c);
		my_len = (nx_ch != NULL) ? (size_t)(nx_ch - s) : ft_strlen(s);
		if (!(r[i] = ft_strsub(s, 0, my_len)))
			return (fr_all(&r[0], i));
		while (*s != c && *s)
			s++;
		i++;
	}
	r[i] = 0;
	return (r);
}
