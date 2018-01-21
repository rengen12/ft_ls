/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 21:02:46 by amichak           #+#    #+#             */
/*   Updated: 2017/10/25 21:22:18 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int	un;

	un = (unsigned int)n;
	if (n < 0)
	{
		ft_putchar('-');
		un = (unsigned int)-n;
	}
	if (un >= 10)
		ft_putnbr(un / 10);
	ft_putchar((char)((un % 10) + '0'));
}
