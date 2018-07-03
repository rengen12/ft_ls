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
# include <time.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <pwd.h>
# include <grp.h>
#include <sys/xattr.h>

typedef struct	s_flags
{
	int 	l;
	int 	o;
	int 	br;
	int 	a;
	int 	ba;
	int 	r;
	int 	f;
	int 	t;
	int 	ac;
	int		st;
}				t_flags;

typedef struct	s_files
{
	mode_t			st_mode;
	nlink_t			st_nlink;
	uid_t			st_uid;
	gid_t			st_gid;
	__darwin_time_t mtime;
	off_t			st_size;
	blkcnt_t		blk;
	dev_t			st_rdev;
	dev_t 			st_dev;
	char 			*name;
	char 			*path;
	struct s_files	*next;
	struct s_files	*prev;
}					t_files;

typedef struct	s_len_ls_l
{
	short int 		l_lmax;
	short int 		usr_lmax;
	short int		gr_lmax;
	short int		sz_lmax;
	int				min;
	int				maj;

}				t_len_ls_l;

void			handle_flags(t_flags *fl, int ac, char **av);

t_files			*find_head(t_files *el);
int				numlen(ssize_t var);
t_files			*find_tail(t_files *el);
void			sort_dll(t_files *fs);
void			sort_dll_t(t_files *fs);

/*temp*/


void	pr(t_files *fs, t_flags fl, int f);
#endif