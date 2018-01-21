/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:43:18 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:43:19 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*send;

	if (!s)
		return (NULL);
	while ((*s == ' ' || *s == '\n' || *s == '\t') && *s)
		s++;
	if (!*s)
		return (ft_strnew(0));
	send = (char *)(s + ft_strlen(s) - 1);
	while (*send == ' ' || *send == '\n' || *send == '\t')
		send--;
	return (ft_strsub(s, 0, (size_t)(send - s + 1)));
}
