/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:30:02 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:30:03 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char *s;

	s = (unsigned char *)src;
	if (s <= (unsigned char *)dest)
		while (n--)
			*((unsigned char *)dest + n) = *(s + n);
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
