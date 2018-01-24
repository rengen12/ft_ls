/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 14:48:00 by amichak           #+#    #+#             */
/*   Updated: 2018/01/24 14:48:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_realloc(char *str, size_t sz)
{
	char	*tmp;
	size_t	n;

	if (!str)
		return (NULL);
	n = ft_strlen(str);
	if (!(tmp = ft_strnew(n + sz)))
		return (NULL);
	ft_memmove(tmp, str, n);
	ft_strdel(&str);
	return (tmp);
}
