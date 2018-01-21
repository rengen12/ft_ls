/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:38:11 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:38:13 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
			r[i] = f(i, r[i]);
			i++;
		}
	}
	return (r);
}
