/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:31:25 by amichak           #+#    #+#             */
/*   Updated: 2017/10/26 15:31:29 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	un;

	un = (unsigned int)n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		un = (unsigned int)-n;
	}
	if (un >= 10)
		ft_putnbr_fd(un / 10, fd);
	ft_putchar_fd((char)(un % 10 + '0'), fd);
}
