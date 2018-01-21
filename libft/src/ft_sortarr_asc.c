/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortarr_asc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:34:03 by amichak           #+#    #+#             */
/*   Updated: 2017/11/02 16:54:21 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_sortarr_asc(int *arr, size_t size)
{
	size_t	i;
	int		f;

	if (size == 0 || !arr)
		return (NULL);
	f = 1;
	while (f)
	{
		f = 0;
		i = 0;
		while (i < size - 1)
			if (arr[i] > arr[i + 1])
			{
				ft_swap(&arr[i], &arr[i + 1]);
				i++;
				f = 1;
			}
	}
	return (arr);
}
