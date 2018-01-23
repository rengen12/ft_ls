/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 20:59:23 by amichak           #+#    #+#             */
/*   Updated: 2017/10/25 21:02:21 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_printf.h"

size_t	ft_putstr_pf(char const *s, t_fs *fs)
{
	size_t	i;

	if (!s)
		return (0);
	i = ft_strlen_printf(s);
	if (fs)
		if (fs->prec_exist && (size_t)fs->prec < i && fs->ch == 's')
			i = fs->prec;
	write(1, s, i);
	return (i);
}
