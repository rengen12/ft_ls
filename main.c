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

t_files	*handle_dir(char *name, t_flags fl)
{
	DIR				*dfd;
	struct dirent	*f;
	struct stat		st;
	t_files			*fs;
	char			*temp;

	fs = NULL;
	temp = NULL;
	if (!(dfd = opendir(name)))
	{
		temp = concat_strs("ls: ", ft_strrchr(name, '/') + 1, NULL);
		perror(temp);
		free(temp);
		return (NULL);
	}
	while ((f = readdir(dfd)))
	{
		if (f->d_name[0] != '.' || (f->d_name[0] == '.' && fl.a))
		{
			add_to_dll(&fs, ft_strdup(f->d_name));
			if (lstat(temp = concat_strs(name, name[ft_strlen(name) - 1] \
											   == '/' ? "" : "/",
										 f->d_name, NULL), &st) >= 0)
				st_cpy(fs, st);
			free(temp);
			if (ft_strcmp(name, "./") && ft_strcmp(f->d_name, "..") &&
				ft_strcmp(f->d_name, "."))
				fs->path = concat_strs(name,
									   name[ft_strlen(name) - 1] == '/' ? ""
																		: "/",
						/*f->d_name, "/",*/ NULL);
			if (errno > 0)
			{
				//perror(concat_strs(name, "/", f->d_name, NULL));
				//errno = 0;
			}
		}
	}
	closedir(dfd);
	sort_dll(fs);
	if (fl.t)
		sort_dll_t(fs);
	return (fs);
}


t_files *handle_dir_rec(char *path, t_flags fl)
{
	t_files *fs;
	t_files *fs2;

	ft_putchar('\n');
	ft_putstr(path);
	ft_putchar(':');
	ft_putchar('\n');
	fs = handle_dir(path, fl);
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
		return (-1);
	if (fs)
	{
		ml = ft_strlen((*fs)->name);
		ml += 8 - ((ml % 8) == 0 ? 8 : ml % 8);
		while ((*fs)->prev)
		{
			if ((res = ft_strlen((*fs)->name)) > ml)
				ml = res;
			ml += 8 - ((ml % 8) == 0 ? 8 : ml % 8);
			*fs = (*fs)->prev;
		}
		if ((res = ft_strlen((*fs)->name)) > ml)
			ml = res;
		ml += 8 - ((ml % 8) == 0 ? 8 : ml % 8);
		while ((*fs)->next)
		{
			if ((res = ft_strlen((*fs)->name)) > ml)
				ml = res;
			ml += 8 - ((ml % 8) == 0 ? 8 : ml % 8);
			*fs = (*fs)->next;
		}
		if ((res = ft_strlen((*fs)->name)) > ml)
			ml = res;
		ml += 8 - ((ml % 8) == 0 ? 8 : ml % 8);
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
		if ((f->name[0] == '.' && fl.a) || f->name[0] != '.')
		{
			if ((temp = numlen(f->st_nlink)) > l->l_lmax)
				l->l_lmax = (short)temp;
			if ((temp = numlen(f->st_size)) > l->sz_lmax)
				l->sz_lmax = (short)temp;
			if ((temp = (int) ft_strlen(get_group(f->st_gid))) > l->gr_lmax)
				l->gr_lmax = (short)temp;
			if ((temp = (int) ft_strlen(get_usr(f->st_uid))) > l->usr_lmax)
				l->usr_lmax = (short)temp;
			if (S_ISCHR(f->st_mode) || S_ISBLK(f->st_mode))
			{
				l->maj = numlen(major(f->st_rdev)) > l->maj ? numlen(
						major(f->st_rdev)) : l->maj;
				l->min = numlen(minor(f->st_rdev)) > l->min ? numlen(
						minor(f->st_rdev)) : l->min;
			}
			if ((f->name[0] == '.' && fl.a) || f->name[0] != '.')
				res += f->blk;
		}
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
		str[11] = ' ';
		str[12] = str[20];
		str[13] = str[21];
		str[14] = str[22];
		str[15] = str[23];
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
		readlink(concat_strs(f->path ? f->path : "", f->name, NULL), link_cont, 1024);
	}
	ft_putchar(S_ISDIR(f->st_mode) ? 'd' : '\0');
	ft_putchar(S_ISFIFO(f->st_mode) ? 'p' : '\0');
	ft_putchar(S_ISCHR(f->st_mode) ? 'c' : '\0');
	ft_putchar(S_ISBLK(f->st_mode) ? 'b' : '\0');
	ft_putchar(S_ISREG(f->st_mode) ? '-' : '\0');
	ft_putchar(S_ISSOCK(f->st_mode) ? 's' : '\0');
	date = get_date(&f->mtime, &len);
	ft_printf("%s%s %*d %-*s  %-*s ", concat_strs((f->st_mode & S_IRUSR) ? "r" : "-", \
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

int 	total_need(t_files *fs, t_flags fl, int f)
{
	while (fs)
	{
		if ((!f && ((fs->name[0] == '.' && fl.a) || fs->name[0] != '.')) || \
                    (f && !S_ISDIR(fs->st_mode)))
			return (1);
		if (fl.r)
			fs = fs->next;
		else
			fs = fs->prev;
	}
	return (0);
}

void	pr_l(t_files *fs, t_flags fl, int f)
{
	int 	sz;
	t_len_ls_l len;

	len = (t_len_ls_l){-1, -1, -1, -1, -1, -1};
	fs = find_tail(fs);
	sz = find_total(fs, fl, &len);
	if (fl.r)
		fs = find_head(fs);
	if (total_need(fs, fl, f))
		ft_printf("total %d\n", sz);
	while (fs)
	{
		if ((!f && ((fs->name[0] == '.' && fl.a) || fs->name[0] != '.')) || \
                    (f && !S_ISDIR(fs->st_mode)))
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
		pr_l(fs, fl, f);
	else
	{
		ioctl(0, TIOCGSIZE, &ts);
		ts.ts_cols += 8 - ((ts.ts_cols % 8) == 0 ? 8 : ts.ts_cols % 8);
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
					newcol += ml + 1;
					ft_printf("%-*s", (newcol + ml + 1 >= ts.ts_cols) ? 0 : ml + 1, fs->name);
					if (newcol + ml + 1 >= ts.ts_cols || fl.o)
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
	//char 	*temp;

	if (!(fs = handle_dir(path, fl)))
	{
		//temp = concat_strs("ls: ", path, NULL);
		//perror(temp);
		//free(temp);
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

int 	ft_pr_pth(t_files *fs, t_flags fl)
{
	int	file;
	int	dir;

	dir = 0;
	file = 0;
	while (fs)
	{
		if (S_ISDIR(fs->st_mode))
			dir++;
		else
			file = 1;
		fs = fs->prev;
	}
	if (dir && file)
		return (2);
	if (dir > 1 || (dir && fl.st < fl.ac))
		return (1);
	return (0);
}

void 	del_node_dll(t_files **cur)
{
	t_files	*prev;
	t_files	*next;

	if (*cur)
	{
		prev = (*cur)->prev;
		next = (*cur)->next;
		if (prev)
			prev->next = (*cur)->next;
		if (next)
			next->prev = (*cur)->prev;
		free((*cur)->name);
		free(*cur);
		*cur = prev;
	}
}

t_files	*parse_av(t_files *fs, t_flags fl, char **av)
{
	char		*temp;
	struct stat st;
	t_files *fs2;
	fs2 = NULL;
	while (fl.st < fl.ac)
			add_to_dll(&fs, ft_strdup(av[fl.st++]));
	sort_dll(fs);
	fs = find_tail(fs);
	while (fs)
	{
		if (lstat(fs->name, &st) < 0)
		{
			temp = concat_strs("ls: ", fs->name, NULL);
			perror(temp);
			free(temp);
			del_node_dll(&fs);
			continue ;
		}
		else
		{
			st_cpy(fs, st);
			fs2 = fs;
		}
		fs = fs->prev;
	}
	sort_dll(fs2);
	if (fl.t)
		sort_dll_t(fs2);
	return (fs2);
}

void	handle_av(t_flags fl, char **av)
{
	t_files *fs;
	t_files *fs2;
	int		pr_pth;

	fs = NULL;
	fs = parse_av(fs, fl, av);
	pr(fs, fl, 1);
	fs = find_tail(fs);
	fs2 = fs;
	pr_pth = ft_pr_pth(fs, fl);
	while (fs)
	{
		if (S_ISDIR(fs->st_mode))
		{
			if (pr_pth)
			{
				if (pr_pth++ > 1)
					ft_putchar('\n');
				ft_putstr(fs->name);
				ft_putstr(":\n");
			}
			handle_av_dir(fl, fs->name);
		}
		fs = fs->prev;
	}
	delete_dll(find_head(fs2));
}


void	handle_ls_without_av(t_flags fl)
{
	t_files *fs;
	t_files	*fs2;

	if (!(fs = handle_dir("./", fl)))
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
		handle_av(fl, av);
	else
		handle_ls_without_av(fl);


	//system("leaks ft_ls");
	/*if (errno == ENOENT || errno == EACCES)
		return (1);*/
	return (0);
}