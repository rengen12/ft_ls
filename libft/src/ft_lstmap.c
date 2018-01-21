/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:28:04 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:28:15 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *r;
	t_list *t2;
	t_list *t;

	if (!lst || !f)
		return (NULL);
	t2 = f(lst);
	if ((r = ft_lstnew(t2->content, t2->content_size)))
	{
		t = r;
		lst = lst->next;
		while (lst)
		{
			t2 = f(lst);
			if (!(t->next = ft_lstnew(t2->content, t2->content_size)))
				return (NULL);
			t = t->next;
			lst = lst->next;
		}
	}
	return (r);
}
