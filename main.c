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
#include <locale.h>
#include "ft_ls.h"


void	sort_dll(t_files *fs);
void	pr(t_files *fs, t_flags fl, int f);
char 	*concat_strs(char *str, ...);
void	pr_st(t_files *head);

t_files *find_el(t_files *head, char *name)
{
	while (head)
	{
		if (!ft_strcmp(head->f->d_name, name))
			return (head);
		head = head->next;
	}
	return (NULL);
}

int		numdlen(ssize_t var)
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

void add_to_dll(t_files **fs, struct dirent *f, char *name)
{
	t_files	*tmp;

	if (fs && (f || name))
	{
		if (!(tmp = (t_files *)malloc(sizeof(t_files))))
			return ;
		tmp->f = f;
		tmp->name = name;
		tmp->next = *fs;
		tmp->prev = NULL;
		if (*fs)
			(*fs)->prev = tmp;
		*fs = tmp;
	}
}

void	delete_dll(t_files *fs)
{
	if (fs)
	{
		if (fs->next)
			delete_dll(fs->next);
		free(fs);
	}
}

t_files	*handle_dir(char *name)
{
	DIR *dfd;
	struct dirent *f;
	struct stat st;
	t_files *fs;

	fs = NULL;
	if (!(dfd = opendir(name)))
		return (NULL);
	while ((f = readdir(dfd)))
	{
		add_to_dll(&fs, f, ft_strdup(f->d_name));
		if (lstat(f->d_name, &st) >= 0)
			fs->st = st;

	}
	closedir(dfd);
	sort_dll(fs);
	return (fs);
}


t_files *handle_dir_rec(char *path, t_flags fl)
{
	t_files *fs;

	ft_putstr(concat_strs("\n", path, ":\n", NULL));
	fs = handle_dir(path);
	pr(fs, fl, 0);
	fs = find_tail(fs);
	while (fs)
	{
		if (fs->f->d_type == DT_DIR && ft_strcmp(fs->f->d_name, ".") && \
				ft_strcmp(fs->f->d_name, ".."))
		{
			if ((fs->f->d_name[0] == '.' && fl.a) || (fs->f->d_name[0] != '.' && !fl.a))
				handle_dir_rec(concat_strs(ft_strcmp(path, "/") == 0 ? "" : path, "/", fs->f->d_name, NULL), fl);
		}
		fs = fs->prev;
	}
	delete_dll(find_head(fs));
	return (fs);
}



void	print_dll(t_files *head)
{
	while (head)
	{
		ft_putendl(head->f->d_name);
		head = head->next;
	}
}

void	print_dll_r(t_files *head)
{
	while (head)
	{
		ft_putendl(head->f->d_name);
		head = head->prev;
	}
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
			if ((fs->name && ft_strcmp(fs->name, fs->next->name) < 0) || (fs->f && \
				ft_strcmp(fs->f->d_name, fs->next->f->d_name) < 0))
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
			if (fs->st.st_mtimespec.tv_sec > fs->next->st.st_mtimespec.tv_sec)
			{
				f = 1;
				dll_paste_aft(fs, fs->next);
			}
			else
				fs = fs->next;
		}
	}
}

size_t	count_col_width(t_files **fs)
{
	size_t	ml;

	ml = 0;
	if (fs)
	{
		ml = ft_strlen((*fs)->f ? (*fs)->f->d_name : (*fs)->name);
		while ((*fs)->prev)
		{
			if (ft_strlen((*fs)->f ? (*fs)->prev->f->d_name : (*fs)->name) > ml)
				ml = ft_strlen((*fs)->f ? (*fs)->prev->f->d_name : (*fs)->name);
			*fs = (*fs)->prev;
		}
		if (ft_strlen((*fs)->f ? (*fs)->f->d_name : (*fs)->name) > ml)
			ml = ft_strlen((*fs)->f ? (*fs)->f->d_name : (*fs)->name);
		while ((*fs)->next)
		{
			if (ft_strlen((*fs)->f ? (*fs)->next->f->d_name : (*fs)->name) > ml)
				ml = ft_strlen((*fs)->f ? (*fs)->next->f->d_name : (*fs)->name);
			*fs = (*fs)->next;
		}
		if (ft_strlen((*fs)->f ? (*fs)->f->d_name : (*fs)->name) > ml)
			ml = ft_strlen((*fs)->f ? (*fs)->f->d_name : (*fs)->name);
	}
	return (ml);
}

int 	find_total(t_files *f, t_flags fl, t_len_ls_l *l)
{
	ssize_t	res;

	res = 0;
	while (f)
	{
		if (numdlen(f->st.st_nlink) > l->l_lmax)
			l->l_lmax = (short)numdlen(f->st.st_nlink);

		if (numdlen(f->st.st_nlink) > l->l_lmax)
			l->gr_lmax = (short)numdlen(f->st.st_nlink);
		if (numdlen(f->st.st_nlink) > l->l_lmax)
			l->sz_lmax = (short)numdlen(f->st.st_nlink);
		if (numdlen(f->st.st_nlink) > l->l_lmax)
			l->usr_lmax = (short)numdlen(f->st.st_nlink);

		if (f->f && ((f->f->d_name[0] == '.' && fl.a) || f->f->d_name[0] != '.'))
			res += f->st.st_blocks;
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

void	pr_l_one_line(t_files *f, t_len_ls_l l)
{
	int 	len;
	char	*date;

	ft_putchar(S_ISLNK(f->st.st_mode) ? 'l' : '\0');
	ft_putchar(S_ISDIR(f->st.st_mode) ? 'd' : '\0');
	ft_putchar(S_ISFIFO(f->st.st_mode) ? 'p' : '\0');
	ft_putchar(S_ISCHR(f->st.st_mode) ? 'c' : '\0');
	ft_putchar(S_ISBLK(f->st.st_mode) ? 'b' : '\0');
	ft_putchar(S_ISREG(f->st.st_mode) ? '-' : '\0');
	ft_putchar(S_ISSOCK(f->st.st_mode) ? 's' : '\0');
	date = get_date(&f->st.st_mtimespec.tv_sec, &len);
	ft_printf("%s%s%3d %s %s %7lld %.*s %s\n", concat_strs((f->st.st_mode & S_IRUSR) ? "r" : "-", \
	(f->st.st_mode & S_IWUSR) ? "w" : "-", (f->st.st_mode & S_IXUSR) ? "x" : "-", \
	(f->st.st_mode & S_IRGRP) ? "r" : "-", (f->st.st_mode & S_IWGRP) ? "w" : "-", \
	(f->st.st_mode & S_IXGRP) ? "x" : "-", (f->st.st_mode & S_IROTH) ? "r" : "-", \
	(f->st.st_mode & S_IWOTH) ? "w" : "-", (f->st.st_mode & S_IXOTH) ? "x" : "-", NULL), \
	(attr(f) > 0 ? "@" : " "), f->st.st_nlink, get_usr(f->st.st_uid), get_group(f->st.st_gid), f->st.st_size, len, date, f->name);
}

void	pr_l(t_files *fs, t_flags fl, int f)
{
	int 	sz;
	t_len_ls_l len;

	len.l_lmax = 0;
	len.usr_lmax = 0;
	len.gr_lmax = 0;
	len.sz_lmax = 0;

	(void)f;
	fs = find_tail(fs);
	sz = find_total(fs, fl, &len);
	if (!sz && !fl.a)
		return ;
	if (fl.r)
		fs = find_head(fs);
	ft_printf("total: %d\n", sz);
	while (fs)
	{
		if (fs->f && ((fs->f->d_name[0] == '.' && fl.a) || fs->f->d_name[0] != '.'))
			pr_l_one_line(fs, len);
		if (fl.r)
			fs = fs->next;
		else
			fs = fs->prev;
	}
}

void	pr(t_files *fs, t_flags fl, int f)
{
	size_t			ml;
	size_t			newcol;
	struct ttysize	ts;

	if (fl.l)
		pr_l(fs, fl, f);
	else
	{
		ioctl(0, TIOCGSIZE, &ts);
		if (fs)
		{
			ml = count_col_width(&fs);
			newcol = 0;
			if (fl.r)
				fs = find_head(fs);
			else
				fs = find_tail(fs);
			while (fs)
			{
				if ((!f && ((fs->f && fs->f->d_name[0] == '.' && fl.a) || (fs->f && fs->f->d_name[0] != '.'))) || \
                    (f && !S_ISDIR(fs->st.st_mode)))
				{
					newcol += ml + 2;
					ft_printf("%-*s", (int) ml + 2, fs->f ? fs->f->d_name : fs->name);
					if (newcol + ml + 2 > ts.ts_cols)
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

	fs = handle_dir(path);
	pr(fs, fl, 0);
	pr_st(find_head(fs));
	if (fl.br)
	{
		fs = find_tail(fs);
		while (fs)
		{
			if (S_ISDIR(fs->st.st_mode))
			{
				handle_dir_rec(concat_strs(path, fs->name, NULL), fl);
			}
			fs = fs->prev;
		}
	}
}

int 	find_2_dir(t_files *fs)
{
	int	res;

	res = 0;
	while (fs)
	{
		if (S_ISDIR(fs->st.st_mode))
			res++;
		if (res >= 2)
			return (1);
		fs = fs->prev;
	}
	return (0);
}

void	pr_st(t_files *head)
{

	while (head)
	{
		ft_printf("%d\n", head->st.st_mtimespec.tv_sec);
		head = head->next;
	}
}

void	handle_av(t_flags *fl, char **av) // ?? star in fl
{
	t_files *fs;
	t_files *fs2;
	struct stat st;
	//char		*path;
	int 		pr_pth;

	fs = NULL;
	while (fl->st < fl->ac)
	{
		if (lstat(av[fl->st], &st) < 0)
		{
			ft_puterr(concat_strs("ls: ", av[fl->st], ": No such file or directory", NULL)); //use perror!
		}
		else
		{
			add_to_dll(&fs, NULL, av[fl->st]);
			fs->st = st;
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
		if (S_ISDIR(fs->st.st_mode))
		{
			if (pr_pth)
				ft_putstr(concat_strs("\n", fs->name, ":\n", NULL));
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

	fs = handle_dir(".");
	sort_dll(fs);
	if (fl.t)
		sort_dll_t(fs);
	pr(fs, fl, 0);
	fs2 = fs;
	if (fl.br)
	{
		fs = find_tail(fs);
		while (fs)
		{
			if (fs->f->d_type == DT_DIR && ft_strcmp(fs->f->d_name, ".") && \
					ft_strcmp(fs->f->d_name, ".."))
				handle_dir_rec(concat_strs("./", fs->f->d_name, NULL), fl);
			fs = fs->prev;
		}
	}
	delete_dll(find_head(fs2));
}

int		main(int ac, char **av)
{
	t_flags	fl;
	setlocale(LC_ALL, "");

	handle_flags(&fl, ac, av);
	if (fl.st)
		handle_av(&fl, av);
	else
		handle_ls_without_av(fl);




	//ft_putendl("origin");
	//print_dll(fs);
	/*sort_dll(fs);
	pr(fs, &fl, 1);
	pr(fs, &fl, 0);*/


	//print_dll(fs);
	//delete_dll(find_head(fs));
	//print_dll(fs);
	/*ft_putendl("sorted");
	fs = find_head(fs);
	print_dll(fs);*/

	//fs = find_head(fs);
	//ft_putendl("\nswapped");
	//print_dll(fs);
	return (0);
}










	/*char *errstr = strerror(3);
	errstr = strerror(2);
	perror(errstr);*/
	//handle_dir();
	/*struct stat fileStat;
	if(stat(av[1],&fileStat) < 0)
		return 1;

	printf("Information for %s\n",av[1]);
	printf("---------------------------\n");
	printf("File Size: \t\t%d bytes\n",fileStat.st_size);
	printf("Number of Links: \t%d\n",fileStat.st_nlink);
	printf("File inode: \t\t%d\n",fileStat.st_ino);

	printf("File Permissions: \t");
	printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
	printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
	printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
	printf("\n\n");

	printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");*/
