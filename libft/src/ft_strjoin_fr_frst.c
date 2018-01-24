/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_fr_frst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:37:28 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:37:30 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_fr_frst(char *s1, char const *s2)
{
	char	*r;

	if (!s1 || !s2)
		return (NULL);
	if (!(r = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(r, s1);
	ft_strcat(r, s2);
	free(s1);
	return (r);
}
