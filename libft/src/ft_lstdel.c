/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:30:11 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:30:12 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*t;
	t_list	*nxt;

	if (alst && del)
	{
		t = *alst;
		while (t)
		{
			nxt = t->next;
			del(t->content, t->content_size);
			free(t);
			t = nxt;
		}
		*alst = NULL;
	}
}
