/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat_pf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 16:28:44 by amichak           #+#    #+#             */
/*   Updated: 2018/01/18 16:28:48 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_printf.h"

char	*ft_strncat_pf(char *dest, const char *src, size_t n)
{
	size_t		l;
	size_t		i;

	i = 0;
	l = ft_strlen_printf(dest);
	while (src[i] && i < n)
	{
		dest[l + i] = src[i];
		i++;
	}
	dest[l + i] = '\0';
	return (dest);
}
