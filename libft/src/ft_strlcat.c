/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:09:30 by amichak           #+#    #+#             */
/*   Updated: 2017/10/26 18:09:33 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (dst[i] != '\0')
		i++;
	k = i;
	while (src[j] != '\0' && size > (k + j + 1))
		dst[i++] = src[j++];
	dst[i] = '\0';
	if (size < k)
		k = size;
	while (*src++ != '\0')
		k++;
	return (k);
}
