/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:28:48 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:28:50 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*cr;

	if (dest == src)
		return (dest);
	cr = (unsigned char *)dest;
	while (n--)
		*cr++ = *((const unsigned char *)src++);
	return (dest);
}
