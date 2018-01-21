/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:28:29 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:28:33 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;
	char	*s1;

	if (n == 0)
		return (NULL);
	i = 0;
	s1 = (char *)dest;
	while (i < n)
	{
		*s1 = *(char *)src++;
		if (*s1++ == (char)c)
			return (s1);
		i++;
	}
	return (NULL);
}
