/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:40:09 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:40:10 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*cp;

	cp = (char *)s;
	while (*++s)
		;
	while (cp != s)
	{
		if (*s == c)
			return ((char *)s);
		s--;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}
