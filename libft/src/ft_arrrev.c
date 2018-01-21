/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:16:54 by amichak           #+#    #+#             */
/*   Updated: 2017/11/03 18:16:56 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrrev(int *arr, size_t size)
{
	int			*r;
	size_t		i;

	i = 0;
	if (!arr || size <= 0)
		return ;
	if (!(r = (int *)malloc(sizeof(*arr) * size)))
		return ;
	while (i < size)
	{
		r[i] = arr[i];
		i++;
	}
	while (size--)
		*arr++ = r[size];
	free(r);
	r = 0;
}
