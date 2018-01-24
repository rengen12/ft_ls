/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:08:33 by amichak           #+#    #+#             */
/*   Updated: 2017/12/28 17:36:30 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

ssize_t		ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	ssize_t	r;

	i = 0;
	r = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			sign = -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		r = r * 10 + (nptr[i] - '0');
		i++;
	}
	if (r > 9223372036854775807 && sign == -1)
		return (0);
	if (r > 9223372036854775807)
		return (-1);
	return (r * sign);
}
