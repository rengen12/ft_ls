#include <stdio.h>
#include "ft_ls.h"
#include <dirent.h>
#include <sys/ioctl.h>

void	sort_dll(t_files *fs);
void	pr(t_files *fs, t_flags *fl, int f);
char 	*concat_strs(char *str, ...);
void	pr_stbuf(t_files *head);

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

/*void dll_paste_aft(t_files *fr, t_files *aft)
{
	t_files *prev;
	t_files	*next;
	t_files	*head;

	if (fr)
	{
		prev = fr->prev;
		next = fr->next;
		if (prev)
			prev->next = next;
		if (next)
			next->prev = prev;
		if (aft)
		{
			fr->next = aft->next;
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
}*/

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
	struct stat stbuf;
	t_files *fs;

	fs = NULL;
	if (!(dfd = opendir(name)))
		return (NULL);
	while ((f = readdir(dfd)))
	{
		add_to_dll(&fs, f, NULL);
		if (lstat(f->d_name, &stbuf) >= 0)
			fs->stbuf = stbuf;
	}
	closedir(dfd);
	sort_dll(fs);
	return (fs);
}


t_files *handle_dir_rec(char *path, t_flags *fl)
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
			if ((fs->f->d_name[0] == '.' && fl->a) || (fs->f->d_name[0] != '.' && !fl->a))
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
			if (fs->stbuf.st_mtimespec.tv_sec > fs->next->stbuf.st_mtimespec.tv_sec)
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

int 	find_total(t_files *fs, t_flags fl)
{
	ssize_t	res;

	res = 0;
	while (fs)
	{
		if ((fs->f && fs->f->d_name[0] == '.' && fl.a) || (fs->f && fs->f->d_name[0] != '.'))) || \
                    (f && !S_ISDIR(fs->stbuf.st_mode)))
		{
		res += fs->stbuf.st_blocks;
		fs = fs->prev;
	}
	return ((int)res);
}

void	pr_l_one_line(t_files *f)
{
	if (S_ISLNK(f->stbuf.st_mode))
		ft_putchar('l');
	else if (S_ISDIR(f->stbuf.st_mode))
		ft_putchar('d');
	else
		ft_putchar('-');
	ft_putchar((f->stbuf.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((f->stbuf.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((f->stbuf.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((f->stbuf.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((f->stbuf.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((f->stbuf.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((f->stbuf.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((f->stbuf.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((f->stbuf.st_mode & S_IXOTH) ? 'x' : '-');

	ft_putchar('\n');
}

void	pr_l(t_files *fs, t_flags *fl, int f)
{
	int 	sz;

	(void)f;
	fs = find_tail(fs);
	sz = find_total(fs);
	if (!sz && !fl->a)
		return ;
	if (fl->r)
		fs = find_head(fs);
	ft_printf("total: %d\n", sz);
	while (fs)
	{
		if ((!f && ((fs->f && fs->f->d_name[0] == '.' && fl->a) || (fs->f && fs->f->d_name[0] != '.'))) || \
                    (f && !S_ISDIR(fs->stbuf.st_mode)))
			pr_l_one_line(fs);
		if (fl->r)
			fs = fs->next;
		else
			fs = fs->prev;
	}
}

void	pr(t_files *fs, t_flags *fl, int f)
{
	size_t			ml;
	size_t			newcol;
	struct ttysize	ts;

	if (fl->l)
		pr_l(fs, fl, f);
	else
	{
		ioctl(0, TIOCGSIZE, &ts);
		if (fs && fl)
		{
			ml = count_col_width(&fs);
			newcol = 0;
			if (fl->r)
				fs = find_head(fs);
			else
				fs = find_tail(fs);
			while (fs)
			{
				if ((!f && ((fs->f && fs->f->d_name[0] == '.' && fl->a) || (fs->f && fs->f->d_name[0] != '.'))) || \
                    (f && !S_ISDIR(fs->stbuf.st_mode)))
				{
					newcol += ml + 2;
					ft_printf("%-*s", (int) ml + 2, fs->f ? fs->f->d_name : fs->name);
					if (newcol + ml + 2 > ts.ts_cols)
					{
						newcol = 0;
						ft_putchar('\n');
					}
				}
				if (fl->r)
					fs = fs->next;
				else
					fs = fs->prev;
			}
			if (newcol)
				ft_putchar('\n');
		}
	}
}

void	handle_av_dir(t_flags *fl, char *path)
{
	t_files *fs;

	fs = handle_dir(path);
	pr(fs, fl, 0);
	pr_stbuf(find_head(fs));
	if (fl->br)
	{
		fs = find_tail(fs);
		while (fs)
		{
			if (S_ISDIR(fs->stbuf.st_mode))
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
		if (S_ISDIR(fs->stbuf.st_mode))
			res++;
		if (res >= 2)
			return (1);
		fs = fs->prev;
	}
	return (0);
}

void	pr_stbuf(t_files *head)
{

	while (head)
	{
		ft_printf("%d\n", head->stbuf.st_mtimespec.tv_sec);
		head = head->next;
	}
}

void	handle_av(t_flags *fl, char **av)
{
	t_files *fs;
	t_files *fs2;
	struct stat stbuf;
	//char		*path;
	int 		pr_pth;

	fs = NULL;
	while (fl->st < fl->ac)
	{
		if (lstat(av[fl->st], &stbuf) < 0)
		{
			ft_puterr(concat_strs("ls: ", av[fl->st], ": No such file or directory", NULL)); //use perror!
		}
		else
		{
			add_to_dll(&fs, NULL, av[fl->st]);
			fs->stbuf = stbuf;
		}
		fl->st++;
	}
	sort_dll(fs);
	if (fl->t)
		sort_dll_t(fs);
	pr(fs, fl, 1);
	fs = find_tail(fs);
	pr_pth = find_2_dir(fs);
	fs2 = fs;
	while (fs)
	{
		if (S_ISDIR(fs->stbuf.st_mode))
		{
			if (pr_pth)
				ft_putstr(concat_strs("\n", fs->name, ":\n", NULL));
			handle_av_dir(fl, fs->name);
		}
		fs = fs->prev;
	}
	delete_dll(find_head(fs2));
}


void	handle_ls_without_av(t_flags *fl)
{
	t_files *fs;
	t_files	*fs2;

	fs = handle_dir(".");
	sort_dll(fs);
	if (fl->t)
		sort_dll_t(fs);
	pr(fs, fl, 0);
	fs2 = fs;
	if (fl->br)
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

	handle_flags(&fl, ac, av);
	if (fl.st)
		handle_av(&fl, av);
	else
		handle_ls_without_av(&fl);

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