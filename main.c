#include <stdio.h>
#include "ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>

void	sort_dll(t_files *fs);
void	just_l(t_files *fs, t_flags *fl, int f);
char 	*concat_strs(char *str, ...);

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
	dfd = opendir(name);
	//dir = (struct dirent *)malloc(sizeof(struct dirent));
	if (!dfd)
	{
		//perror(strerror(errno));
		return (NULL);
	}
	//ft_putnbr(lstat("../libft/src", &stbuf));
	while ((f = readdir(dfd)))
	{
		/*if (!ft_strcmp(f->d_name, ".") || !ft_strcmp(f->d_name, ".."))
			continue ;*/
		add_to_dll(&fs, f, NULL);
		lstat(f->d_name, &stbuf);
	}
	closedir(dfd);
	return (fs);
}


t_files *handle_dir_rec(char *path, t_flags *fl)
{
	t_files *fs;

	//ft_putendl("");
	ft_putstr(concat_strs("\n", path, ":\n", NULL));
	fs = handle_dir(path);
	sort_dll(fs);
	just_l(fs, fl, 1);
	just_l(fs, fl, 0);
	fs = find_tail(fs);
	while (fs)
	{
		if (fs->f->d_type == DT_DIR && ft_strcmp(fs->f->d_name, ".") && \
				ft_strcmp(fs->f->d_name, ".."))
		{
			handle_dir_rec(concat_strs(path, "/", fs->f->d_name, NULL), fl);
		}
		fs = fs->prev;
	}
	delete_dll(find_head(fs));
	return (fs);
}

void	handle_flags(t_flags *fl, int ac, char **av)
{
	int i;

	i = 0;
	fl->a = 0;
	fl->br = 0;
	fl->l = 0;
	fl->r = 0;
	fl->t = 0;
	fl->ac = ac;
	while (++i < ac && av[i][0] == '-')
		while (*++av[i])
				if (*av[i] == 'a')
					fl->a = 1;
				else if (*av[i] == 'R')
					fl->br = 1;
				else if (*av[i] == 'l')
					fl->l = 1;
				else if (*av[i] == 'r')
					fl->r = 1;
				else if (*av[i] == 't')
					fl->t = 1;
	fl->st = (i < ac) ? i : 0;
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
			//print_dll(find_head(fs));
		}
		//write(1, "11\n", 3);
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

void just_l(t_files *fs, t_flags *fl, int f)
{
	size_t	ml;
	size_t	newcol;
	struct ttysize ts;
	ioctl(0, TIOCGSIZE, &ts);

	if (fs && fl)
	{
		ml = count_col_width(&fs);
		newcol = 0;
		if (fl->r)
			fs = find_head(fs);
		while (fs)
		{
			if ((!f && ((fs->f && fs->f->d_name[0] == '.' && fl->a) || (fs->f && fs->f->d_name[0] != '.'))) || (f && fs->name))
			{
				newcol += ml + 2;
				ft_printf("%-*s", (int)ml + 2, fs->f ? fs->f->d_name : fs->name);
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
	}
}

char 	*concat_strs(char *str, ...)
{
	va_list ap;
	char	*res;

	res = NULL;
	if (str)
	{
		va_start(ap, str);
		if (!(res = ft_strnew(ft_strlen(str))))
			return (NULL);
		ft_strcpy(res, str);
		while ((str = va_arg(ap, char *)))
		{
			res = ft_realloc(res, ft_strlen(str));
			ft_strcat(res, str);
		}

		va_end(ap);
	}
	return (res);
}

t_files	*handle_av(t_flags *fl, char **av)
{
	t_files *fs;
	struct stat stbuf;
	//char		*path;

	fs = NULL;
	while (fl->st < fl->ac)
	{
		if (lstat(av[fl->st], &stbuf) < 0)
		{
			ft_puterr(concat_strs("ls: ", av[fl->st], ": No such file or directory", NULL));
		}
		else
		{
			add_to_dll(&fs, NULL, av[fl->st]);
		}
		fl->st++;
	}
	sort_dll(fs);
	just_l(fs, fl, 1);
	just_l(fs, fl, 0);
	if (fl->br)
	{
		fs = find_tail(fs);
		while (fs)
		{
			if (lstat(fs->name, &stbuf) >= 0)
				if (S_ISDIR(stbuf.st_mode))
				{
					handle_dir_rec(fs->name, fl);
				}
			fs = fs->prev;
		}
	}
	delete_dll(find_head(fs));
	return (fs);
}

t_files	*handle_ls_without_av(t_flags *fl)
{
	t_files *fs;

	fs = handle_dir(".");

	/*ft_putendl("not_sotred");
	print_dll(fs);
	ft_putendl("");*/
	sort_dll(fs);
	/*ft_putendl("sotred");
	print_dll(find_head(fs));
	ft_putendl("");
	ft_putendl("rev");
	print_dll_r(find_tail(fs));*/
	just_l(fs, fl, 0);
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
	return (fs);
}

int		main(int ac, char **av)
{
	t_flags	fl;
	t_files *fs;

	//printf("S_IFDIR %d\n", S_IFDIR);
	//printf("S_IFMT %d\n", S_IFMT);
	handle_flags(&fl, ac, av);
	if (fl.st)
	{
		fs = handle_av(&fl, av);
	}
	else
		fs = handle_ls_without_av(&fl);

	//ft_putendl("origin");
	//print_dll(fs);

	/*sort_dll(fs);
	just_l(fs, &fl, 1);
	just_l(fs, &fl, 0);
	*/


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