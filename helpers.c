/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 13:05:00 by amichak           #+#    #+#             */
/*   Updated: 2018/02/09 13:05:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


/*NU*/
t_files *find_el(t_files *head, char *name)
{
	while (head)
	{
		if (!ft_strcmp(head->name, name))
			return (head);
		head = head->next;
	}
	return (NULL);
}

int		numlen(ssize_t var)
{
	int	i;

	i = 0;
	while (var)
	{
		var /= 10;
		i++;
	}
	if (!i)
		i = 1;
	return (i);
}

int 	is_head(t_files *fr)
{
	if (!fr->prev)
		return (1);
	return (0);
}

t_files	*find_head(t_files *el)
{
	if (el)
		while (el->prev)
			el = el->prev;
	return (el);
}

t_files	*find_tail(t_files *el)
{
	if (el)
		while (el->next)
			el = el->next;
	return (el);
}
