/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:29:56 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:29:59 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*cs;

	if (n == 0)
		return (s);
	cs = (unsigned char *)s;
	while (n--)
	{
		*cs = (unsigned char)c;
		if (n)
			cs++;
	}
	return (s);
}
