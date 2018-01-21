/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modificators.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 20:24:00 by amichak           #+#    #+#             */
/*   Updated: 2017/12/26 20:24:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_printf.h"

void	usemodifu(t_fs *fs, size_t *valu)
{
	if (fs->h && *valu && !fs->l)
		if (fs->h == 1)
			*valu = (unsigned short int)*valu;
		else
			*valu = (unsigned char)*valu;
	else if ((fs->l && *valu) || fs->ch == 'p' || fs->ch == 'O')
		if (fs->l == 1 || fs->ch == 'p' || fs->ch == 'O')
			*valu = (unsigned long int)*valu;
		else
			*valu = (unsigned long long int)*valu;
	else if (fs->j && *valu)
		*valu = (uintmax_t) * valu;
	else if (fs->z)
		*valu = (size_t)*valu;
	else
		*valu = (unsigned int)*valu;
}

void	usemodifs(t_fs *fs, ssize_t *vals)
{
	if (fs->h && *vals && !fs->l && !fs->z && !fs->j)
		if (fs->h == 1)
			*vals = (short int)*vals;
		else
			*vals = (char)*vals;
	else if (fs->l && *vals)
		if (fs->l == 1)
			*vals = (long int)*vals;
		else
			*vals = (long long int)*vals;
	else if (fs->j && *vals)
		*vals = (intmax_t) * vals;
	else if (fs->z)
		*vals = (size_t)*vals;
	else
		*vals = (int)*vals;
}
