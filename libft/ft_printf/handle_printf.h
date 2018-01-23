/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_printf.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 18:43:00 by amichak           #+#    #+#             */
/*   Updated: 2017/12/26 18:43:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_PRINTF_H
# define HANDLE_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <limits.h>
# include <inttypes.h>

# define ABS(a) ((a < 0) ? (-a) : (a))

# define EOC          "\x1b[0m"

# define BLACK        "\x1b[30m"
# define RED          "\x1b[31m"
# define GREEN        "\x1b[32m"
# define YELLOW       "\x1b[33m"
# define BLUE         "\x1b[34m"
# define MAGENTA      "\x1b[35m"
# define CYAN         "\x1b[36m"
# define WHITE        "\x1b[37m"

# define BLACK_BG     "\x1b[40m"
# define RED_BG   	 "\x1b[41m"
# define GREEN_BG     "\x1b[42m"
# define YELLOW_BG    "\x1b[43m"
# define BLUE_BG      "\x1b[44m"
# define MAGENTA_BG   "\x1b[45m"
# define CYAN_BG      "\x1b[46m"
# define WHITE_BG     "\x1b[47m"

# define BOLD         "\x1b[1m"
# define ITALIC       "\x1b[3m"
# define UNDERLINE    "\x1b[4m"
# define BLINK        "\x1b[5m"
# define INVERTED     "\x1b[7m"
# define INVISIBLE    "\x1b[8m"

typedef struct	s_fs
{
	char	ch;
	int		nf;

	int		sh;
	int		zero;
	int		minus;
	int		plus;
	int		space;

	int		width;
	int		prec;
	int		prec_exist;

	int		h;
	int		l;
	int		j;
	int		z;

}				t_fs;

int				ft_putchar_u(size_t c);
size_t			ft_putstr_u(char *s);
char			*ft_convert_base_printf(size_t nb, char *base_to, t_fs *fs);
size_t			ft_putchar_pf(char c);
size_t			ft_putstr_pf(char const *s, t_fs *fs);
size_t			ft_strlen_printf(const char *s);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
char			*ft_strncat_pf(char *dest, const char *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
size_t			ft_putnbr_prntf(ssize_t n, t_fs *fs);
void			ft_strdel(char **as);
size_t			padding_afsign(t_fs *fs, int wordlen);
int				ft_wordlen(ssize_t var);
void			usemodifu(t_fs *fs, size_t *valu);
void			usemodifs(t_fs *fs, ssize_t *vals);
size_t			ft_strlen_u(char *s, t_fs *fs);
int				ft_atoi_printf(const char **nptr);
char			*ft_strchr(const char *s, int c);
size_t			ft_putnstr_u(char *s, size_t len);
int				ft_strcmp_pf(const char *s1, const char *s2);
void			parse_color(char const **s);
size_t			handle_sharp(size_t nb, t_fs *fs);
size_t			print_str_fs(t_fs *fs, va_list ap);
size_t			print_ordsymb(const char **s);
void			read_conv_mod(t_fs *fs, const char **s);
size_t			handle_str_fs(va_list ap, const char **s, t_fs *fs);
size_t			padding(t_fs *fs, int wordlen);
size_t			padding_after(t_fs *fs, int wordlen);
size_t			padding_str(t_fs *fs, int wordlen);
size_t			print_num(t_fs *fs, va_list ap);
size_t			print_unsig(t_fs *fs, va_list ap);
size_t			print_float(t_fs *fs, va_list ap);
size_t			print_char(t_fs *fs, va_list ap);
size_t			print_string(t_fs *fs, va_list ap);
size_t			print_float(t_fs *fs, va_list ap);

#endif
