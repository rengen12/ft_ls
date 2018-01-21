/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraymin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:25:34 by amichak           #+#    #+#             */
/*   Updated: 2017/11/02 16:25:35 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_arraymin(int *arr, size_t size)
{
	int			min;
	size_t		i;

	if (size == 0 || !arr)
	{
		return (0);
	}
	i = 0;
	min = arr[i];
	while (++i < size)
		if (arr[i] < min)
			min = arr[i];
	return (min);
}
