/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 16:32:35 by amichak           #+#    #+#             */
/*   Updated: 2018/01/18 16:32:37 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putarr(int *arr, int len, char separator)
{
	int		i;

	i = 0;
	while (i < len)
	{
		ft_putnbr(arr[i++]);
		if (i < len)
			ft_putchar(separator);
		else
			ft_putchar('\n');
	}
}
