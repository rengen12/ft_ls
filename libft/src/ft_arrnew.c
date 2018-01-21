/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 16:30:04 by amichak           #+#    #+#             */
/*   Updated: 2018/01/18 16:30:06 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_arrnew(int len)
{
	int	*mas;

	if (!(mas = (int *)malloc(sizeof(int) * len)))
		return (NULL);
	return (ft_memset(mas, 0, len));
}
