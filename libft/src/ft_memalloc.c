/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:28:16 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:28:25 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memalloc(size_t size)
{
	void	*r;

	if (!(r = malloc(size)))
		return (NULL);
	ft_bzero(r, size);
	return (r);
}
