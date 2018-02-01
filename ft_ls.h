/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:07:00 by amichak           #+#    #+#             */
/*   Updated: 2018/01/21 15:07:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>

typedef struct	s_flags
{
	int 	l;
	int 	br;
	int 	a;
	int 	r;
	int 	t;
	int 	ac;
	int		st;
}				t_flags;

typedef struct	s_files
{
	struct dirent	*f;
	char 			*name;
	struct stat		stbuf;
	struct s_files	*next;
	struct s_files	*prev;
}				t_files;

void			handle_flags(t_flags *fl, int ac, char **av);

#endif