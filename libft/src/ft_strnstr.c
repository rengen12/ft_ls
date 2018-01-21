/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:39:48 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:39:52 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	char	*cp;

	if (!*needle)
		return ((char *)haystack);
	while (*haystack && n > 0)
	{
		i = 0;
		cp = (char *)haystack;
		while (*cp++ == needle[i] && needle[i] && i < n)
			i++;
		if (!needle[i])
			return ((char *)haystack);
		haystack++;
		n--;
	}
	return (NULL);
}
