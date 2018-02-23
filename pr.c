/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 13:16:00 by amichak           #+#    #+#             */
/*   Updated: 2018/02/09 13:16:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*NU*/
void	print_dll(t_files *head)
{
	while (head)
	{
		ft_putendl(head->name);
		head = head->next;
	}
}
/*NU*/
void	print_dll_r(t_files *head)
{
	while (head)
	{
		ft_putendl(head->name);
		head = head->prev;
	}
}
/*NU*/
void	pr_st(t_files *head)
{

	while (head)
	{
		ft_printf("%d\n", head->mtime);
		head = head->next;
	}
}