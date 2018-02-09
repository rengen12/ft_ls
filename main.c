/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 12:37:32 by amichak           #+#    #+#             */
/*   Updated: 2018/02/02 12:37:34 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_ls.h"

void add_to_dll(t_files **fs, char *name)
{
	t_files	*tmp;

	if (fs && name)
	{
		if (!(tmp = (t_files *)malloc(sizeof(t_files))))
			return ;
		tmp->name = name;
		tmp->next = *fs;
		tmp->prev = NULL;
		tmp->path = NULL;
		if (*fs)
			(*fs)->prev = tmp;
		*fs = tmp;
	}
}

void	delete_dll(t_files *fs)
{
	if (fs)
	{
		if (fs->name)
			free(fs->name);
		if (fs->path)
			free(fs->path);
		if (fs->next)
			delete_dll(fs->next);
		free(fs);
	}
}

void	st_cpy(t_files *fs, struct stat st)
{
	fs->st_mode = st.st_mode;
	fs->st_nlink = st.st_nlink;
	fs->st_uid = st.st_uid;
	fs->st_gid = st.st_gid;
	fs->mtime = st.st_mtimespec.tv_sec;
	fs->st_size = st.st_size;
	fs->blk = st.st_blocks;
	fs->st_dev = st.st_dev;
	fs->st_rdev = st.st_rdev;
}

t_files	*handle_dir(char *name)
{
	DIR *dfd;
	struct dirent *f;
	struct stat st;
	t_files *fs;
	char	*temp; /*NU*/

	fs = NULL;
	temp = NULL;
	if (!(dfd = opendir(name)))
		return (NULL);
	while ((f = readdir(dfd)))
	{
		add_to_dll(&fs, ft_strdup(f->d_name));
		if (lstat(temp = concat_strs(name, name[ft_strlen(name) - 1] == '/' ? "" : "/", f->d_name, NULL), &st) >= 0)
		{
			st_cpy(fs, st);
			free(temp);
		}
		if (ft_strcmp(name, "./"))
			fs->path = concat_strs(name,
								   name[ft_strlen(name) - 1] == '/' ? "" : "/",
								   f->d_name, "/", NULL);
		if (errno > 0)
		{
			//perror(concat_strs(name, "/", f->d_name, NULL));
			//errno = 0;
		}
	}
	closedir(dfd);
	sort_dll(fs);
	return (fs);
}


t_files *handle_dir_rec(char *path, t_flags fl)
{
	t_files *fs;
	t_files *fs2;

	ft_putchar('\n');
	ft_putstr(path);
	ft_putchar('\n');
	fs = handle_dir(path);
	if (fs)
	{
		fs = find_tail(fs);
		pr(fs, fl, 0);
		fs2 = fs;
		while (fs)
		{
			if (S_ISDIR(fs->st_mode) && ft_strcmp(fs->name, ".") && \
                    ft_strcmp(fs->name, ".."))
			{
				if ((fs->name[0] == '.' && fl.a) || fs->name[0] != '.')
					handle_dir_rec(concat_strs(path, "/", fs->name, NULL), fl);
			}
			fs = fs->prev;
		}
		delete_dll(find_head(fs2));
	}
	free(path);
	return (fs);
}

int		count_col_width(t_files **fs, t_flags fl)
{
	size_t	ml;
	size_t	res;

	ml = 0;
	if (fl.o)
		return (-2);
	if (fs)
	{
		ml = ft_strlen((*fs)->name);
		while ((*fs)->prev)
		{
			if ((res = ft_strlen((*fs)->name)) > ml)
				ml = res;
			*fs = (*fs)->prev;
		}
		if ((res = ft_strlen((*fs)->name)) > ml)
			ml = res;
		while ((*fs)->next)
		{
			if ((res = ft_strlen((*fs)->name)) > ml)
				ml = res;
			*fs = (*fs)->next;
		}
		if ((res = ft_strlen((*fs)->name)) > ml)
			ml = res;
	}
	return ((int)ml);
}

char	*get_usr(uid_t uid)
{
	return (getpwuid(uid)->pw_name);
}

char	*get_group(uid_t uid)
{
	return (getgrgid(uid)->gr_name);
}

ssize_t attr(t_files *f)
{
	return (listxattr(f->name, NULL, 0, 0));
}

int 	find_total(t_files *f, t_flags fl, t_len_ls_l *l)
{
	ssize_t	res;
	int 	temp;

	res = 0;
	while (f)
	{
		if ((temp = numlen(f->st_nlink)) > l->l_lmax)
			l->l_lmax = (short)temp;
		if ((temp = numlen(f->st_size)) > l->sz_lmax)
			l->sz_lmax = (short)temp;
		if ((temp = (int)ft_strlen(get_group(f->st_gid))) > l->gr_lmax)
			l->gr_lmax = (short)temp;
		if ((temp = (int)ft_strlen(get_usr(f->st_uid))) > l->l_lmax)
			l->usr_lmax = (short)temp;
		if (S_ISCHR(f->st_mode) || S_ISBLK(f->st_mode))
		{
			l->maj = numlen(major(f->st_rdev)) > l->maj ? numlen(major(f->st_rdev)) : l->maj;
			l->min = numlen(minor(f->st_rdev)) > l->min ? numlen(minor(f->st_rdev)) : l->min;
		}
		if ((f->name[0] == '.' && fl.a) || f->name[0] != '.')
			res += f->blk;
		f = f->prev;
	}
	return ((int)res);
}

char	*get_date(long *val, int *len)
{
	char *str;

	str = ctime(val);
	if (*val < time(NULL) - 15552000)
	{
		*len = 4;
		return (str + 20);
	}
	*len = 12;
	return (str + 4);
}

void	print_maj_min(t_files *f, t_len_ls_l l)
{
	ft_printf("%*d, %*d", l.maj, major(f->st_rdev), l.min, minor(f->st_rdev));
}

void	pr_l_one_line(t_files *f, t_len_ls_l l)
{
	char	*date;
	int 	len;
	char 	*link_cont;

	link_cont = NULL;
	if (S_ISLNK(f->st_mode))
	{
		ft_putchar('l');
		link_cont = ft_strnew(1024);
		readlink(concat_strs(f->path ? f->path : "", f->name, NULL), link_cont, sizeof(link_cont));
	}
	ft_putchar(S_ISDIR(f->st_mode) ? 'd' : '\0');
	ft_putchar(S_ISFIFO(f->st_mode) ? 'p' : '\0');
	ft_putchar(S_ISCHR(f->st_mode) ? 'c' : '\0');
	ft_putchar(S_ISBLK(f->st_mode) ? 'b' : '\0');
	ft_putchar(S_ISREG(f->st_mode) ? '-' : '\0');
	ft_putchar(S_ISSOCK(f->st_mode) ? 's' : '\0');
	date = get_date(&f->mtime, &len);
	/*ft_printf("%s%s %*d %.*s  %.*s  %*d %.*s %s%s\n", concat_strs((f->st_mode & S_IRUSR) ? "r" : "-", \
	(f->st_mode & S_IWUSR) ? "w" : "-", (f->st_mode & S_IXUSR) ? "x" : "-", \
	(f->st_mode & S_IRGRP) ? "r" : "-", (f->st_mode & S_IWGRP) ? "w" : "-", \
	(f->st_mode & S_IXGRP) ? "x" : "-", (f->st_mode & S_IROTH) ? "r" : "-", \
	(f->st_mode & S_IWOTH) ? "w" : "-", (f->st_mode & S_IXOTH) ? "x" : "-", NULL), \
	(attr(f) > 0 ? "@" : " "), l.l_lmax, f->st_nlink, l.usr_lmax, get_usr(f->st_uid), \
	l.gr_lmax, get_group(f->st_gid), l.sz_lmax, f->st_size, len, date, f->name, \
	S_ISLNK(f->st_mode) ? concat_strs(" -> ", link_cont, NULL) : "");*/
	ft_printf("%s%s %*d %.*s  %.*s  ", concat_strs((f->st_mode & S_IRUSR) ? "r" : "-", \
		(f->st_mode & S_IWUSR) ? "w" : "-", (f->st_mode & S_IXUSR) ? "x" : "-", \
		(f->st_mode & S_IRGRP) ? "r" : "-", (f->st_mode & S_IWGRP) ? "w" : "-", \
		(f->st_mode & S_IXGRP) ? "x" : "-", (f->st_mode & S_IROTH) ? "r" : "-", \
		(f->st_mode & S_IWOTH) ? "w" : "-", (f->st_mode & S_IXOTH) ? "x" : "-", NULL), \
		(attr(f) > 0 ? "@" : " "), l.l_lmax, f->st_nlink, l.usr_lmax, get_usr(f->st_uid), \
		l.gr_lmax, get_group(f->st_gid));
	if (S_ISBLK(f->st_mode) || S_ISCHR(f->st_mode))
		print_maj_min(f, l);
	else
		ft_printf("%*d", l.sz_lmax, f->st_size);
	ft_printf(" %.*s %s%s\n", len, date, f->name, \
			  S_ISLNK(f->st_mode) ? concat_strs(" -> ", link_cont, NULL) : "");
	if (S_ISLNK(f->st_mode))
		free(link_cont);
}

void	pr_l(t_files *fs, t_flags fl)
{
	int 	sz;
	t_len_ls_l len;

	len = (t_len_ls_l){0, 0, 0, 0, 0, 0};
	fs = find_tail(fs);
	sz = find_total(fs, fl, &len);
//	if (!sz && !fl.a)
		//return ;
	if (fl.r)
		fs = find_head(fs);
	ft_printf("total %d\n", sz);
	while (fs)
	{
		if ((fs->name[0] == '.' && fl.a) || fs->name[0] != '.')
			pr_l_one_line(fs, len);
		if (fl.r)
			fs = fs->next;
		else
			fs = fs->prev;
	}
}

void	pr(t_files *fs, t_flags fl, int f)
{
	int				ml;
	size_t			newcol;
	struct ttysize	ts;

	if (fl.l)
		pr_l(fs, fl);
	else
	{
		ioctl(0, TIOCGSIZE, &ts);
		if (fs)
		{
			ml = count_col_width(&fs, fl);
			newcol = 0;
			if (fl.r)
				fs = find_head(fs);
			else
				fs = find_tail(fs);
			while (fs)
			{
				if ((!f && ((fs->name[0] == '.' && fl.a) || fs->name[0] != '.')) || \
                    (f && !S_ISDIR(fs->st_mode)))
				{
					newcol += ml + 2;
					ft_printf("%-*s", ml + 2, fs->name);
					if (newcol + ml + 2 > ts.ts_cols || fl.o)
					{
						newcol = 0;
						ft_putchar('\n');
					}
				}
				if (fl.r)
					fs = fs->next;
				else
					fs = fs->prev;
			}
			if (newcol)
				ft_putchar('\n');
		}
	}
}

void	handle_av_dir(t_flags fl, char *path)
{
	t_files *fs;
	t_files *fs2;
	char 	*temp;

	temp = NULL;
	if (!(fs = handle_dir(path)))
	{
		temp = concat_strs("ls: ", path, NULL);
		perror(temp);
		free(temp);
		return ;
	}
	fs2 = fs;
	pr(fs, fl, 0);
	if (fl.br)
	{
		fs = find_tail(fs);
		while (fs)
		{
			if (S_ISDIR(fs->st_mode) && ft_strcmp(fs->name, ".") && \
				ft_strcmp(fs->name, ".."))
			{
				if ((fs->name[0] == '.' && fl.a) || fs->name[0] != '.')
					handle_dir_rec(concat_strs(path, path[ft_strlen(path) - 1] == '/'
													 ? "" : "/", fs->name, NULL), fl);
			}
			fs = fs->prev;
		}
	}
	delete_dll(find_head(fs2));
}

int 	find_2_dir(t_files *fs)
{
	int	res;

	res = 0;
	while (fs)
	{
		if (S_ISDIR(fs->st_mode))
			res++;
		if (res >= 2)
			return (1);
		fs = fs->prev;
	}
	return (0);
}



void	handle_av(t_flags *fl, char **av) // ?? star in fl
{
	t_files *fs;
	t_files *fs2;
	struct stat st;
	int 		pr_pth;
	char		*temp;

	fs = NULL;
	temp = NULL;
	while (fl->st < fl->ac)
	{
		if (lstat(av[fl->st], &st) < 0)
		{
			temp = concat_strs("ls: ", av[fl->st], NULL);
			perror(temp);
			free(temp);
		}
		else
		{
			add_to_dll(&fs, ft_strdup(av[fl->st]));
			st_cpy(fs, st);
		}
		fl->st++; //changed value in use???
	}
	sort_dll(fs);
	if (fl->t)
		sort_dll_t(fs);
	pr(fs, *fl, 1);
	fs = find_tail(fs);
	pr_pth = find_2_dir(fs);
	fs2 = fs;
	while (fs)
	{
		if (S_ISDIR(fs->st_mode))
		{
			if (pr_pth)
			{
				ft_putchar('\n');
				ft_putstr(fs->name);
				ft_putchar('\n');
			}
			handle_av_dir(*fl, fs->name);
		}
		fs = fs->prev;
	}
	delete_dll(find_head(fs2));
}


void	handle_ls_without_av(t_flags fl)
{
	t_files *fs;
	t_files	*fs2;

	if (!(fs = handle_dir("./")))
		return ;
	if (fl.t)
		sort_dll_t(fs);
	pr(fs, fl, 0);
	fs2 = fs;
	if (fl.br)
	{
		fs = find_tail(fs);
		while (fs)
		{
			if (S_ISDIR(fs->st_mode) && ft_strcmp(fs->name, ".") && \
					ft_strcmp(fs->name, ".."))
				handle_dir_rec(concat_strs("./", fs->name, NULL), fl);
			fs = fs->prev;
		}
	}
	delete_dll(find_head(fs2));
}

int		main(int ac, char **av)
{
	t_flags	fl;

	handle_flags(&fl, ac, av);
	if (fl.st)
		handle_av(&fl, av);
	else
		handle_ls_without_av(fl);

	//system("leaks ft_ls");
	if (errno == ENOENT || errno == EACCES)
		return (1);
	return (0);
}