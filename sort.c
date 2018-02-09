/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 13:26:00 by amichak           #+#    #+#             */
/*   Updated: 2018/02/09 13:26:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void dll_paste_aft(t_files *fr, t_files *aft)
{
	t_files	*head;

	if (!fr)
		return ;
	if (aft)
	{
		fr->next = aft->next;
		aft->prev = fr->prev;
		if (aft->next)
			aft->next->prev = fr;
		if (fr->prev)
			fr->prev->next = aft;
		aft->next = fr;
	}
	else
	{
		head = find_head(fr);
		fr->next = head;
		head->prev = fr;
	}
	fr->prev = aft;
}

void	sort_dll(t_files *fs)
{
	int f;

	f = 1;
	while (f && fs)
	{
		f = 0;
		fs = find_head(fs);
		while (fs->next)
		{
			if (ft_strcmp(fs->name, fs->next->name) < 0)
			{
				f = 1;
				dll_paste_aft(fs, fs->next);
			}
			else
				fs = fs->next;
		}
	}
}

void	sort_dll_t(t_files *fs)
{
	int 	f;

	f = 1;
	while (f && fs)
	{
		f = 0;
		fs = find_head(fs);
		while (fs->next)
		{
			if (fs->mtime > fs->next->mtime)
			{
				f = 1;
				dll_paste_aft(fs, fs->next);
			}
			else
				fs = fs->next;
		}
	}
}
