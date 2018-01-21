/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:38:04 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:38:06 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*r;
	unsigned int	i;

	r = NULL;
	if (s && f)
	{
		if (!(r = ft_strnew(ft_strlen(s))))
			return (NULL);
		ft_strcpy(r, s);
		i = 0;
		while (r[i])
		{
			r[i] = f(r[i]);
			i++;
		}
	}
	return (r);
}
