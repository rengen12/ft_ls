/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:27:21 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:27:28 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*n;

	if (!(n = (t_list *)malloc(sizeof(*n))))
		return (NULL);
	if (!content)
	{
		n->content = NULL;
		n->content_size = 0;
	}
	else
	{
		if (!(n->content = malloc(content_size)))
			return (NULL);
		ft_memmove(n->content, content, content_size);
		n->content_size = content_size;
	}
	n->next = NULL;
	return (n);
}
