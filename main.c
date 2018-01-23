#include <stdio.h>
#include "ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "libft/ft_printf/ft_printf.c"

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

void dll_paste_aft(t_files *fr, t_files *aft)
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
}

void add_to_dll(t_files **fs, struct dirent *f)
{
	t_files	*tmp;

	if (fs && f)
	{
		if (!(tmp = (t_files *)malloc(sizeof(t_files))))
			return ;
		tmp->f = f;
		tmp->next = *fs;
		tmp->prev = NULL;
		if (*fs)
			(*fs)->prev = tmp;
		*fs = tmp;
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
		perror(strerror(errno));
		return (NULL);
	}
	while ((f = readdir(dfd)))
	{
		/*if (!ft_strcmp(f->d_name, ".") || !ft_strcmp(f->d_name, ".."))
			continue ;*/
		add_to_dll(&fs, f);
		stat(f->d_name, &stbuf);
	}
	closedir(dfd);
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

void	sort_dll(t_files *fs)
{
	int f;

	f = 1;
	while (f && fs)
	{
		f = 0;
		fs = find_head(fs);
		while (fs->next)
			if (ft_strcmp(fs->f->d_name, fs->next->f->d_name) < 0)
			{
				f = 1;
				dll_paste_aft(fs, fs->next);
			}
			else
				fs = fs->next;
	}
}

size_t	count_col_width(t_files **fs)
{
	size_t	ml;

	ml = 0;
	if (fs)
	{
		ml = ft_strlen((*fs)->f->d_name);
		while ((*fs)->prev)
		{
			if (ft_strlen((*fs)->prev->f->d_name) > ml)
				ml = ft_strlen((*fs)->prev->f->d_name);
			*fs = (*fs)->prev;
		}
		if (ft_strlen((*fs)->f->d_name) > ml)
			ml = ft_strlen((*fs)->f->d_name);
		while ((*fs)->next)
		{
			if (ft_strlen((*fs)->next->f->d_name) > ml)
				ml = ft_strlen((*fs)->next->f->d_name);
			*fs = (*fs)->next;
		}
		if (ft_strlen((*fs)->f->d_name) > ml)
			ml = ft_strlen((*fs)->f->d_name);
	}
	return (ml);
}

void just_l(t_files *fs, t_flags *fl)
{
	size_t	ml;
	size_t	newcol;

	if (fs && fl)
	{
		ml = count_col_width(&fs); //need new start position??
		newcol = 0;
		while (fs)
		{
			if ((fs->f->d_name[0] == '.' && fl->a) || fs->f->d_name[0] != '.')
			{
				newcol += ml + 2;
				ft_printf("%-*s", (int)ml + 2, fs->f->d_name);
				if (newcol + ml + 2 > 80)
				{
					newcol = 0;
					ft_putchar('\n');
				}
			}
			fs = fs->prev;
		}
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

int		main(int ac, char **av)
{
	t_flags	fl;
	t_files *fs;

	//printf("S_IFDIR %d\n", S_IFDIR);
	//printf("S_IFMT %d\n", S_IFMT);
	handle_flags(&fl, ac, av);
	fs = handle_dir("../libft");

	//ft_putendl("origin");
	//print_dll(fs);

	sort_dll(fs);
	just_l(fs, &fl);
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