# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amichak <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/11 13:15:45 by amichak           #+#    #+#              #
#    Updated: 2017/11/15 19:41:01 by amichak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:				all clean fclean re $(NAME)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
HEADER = -I ./
OBJFOLD = src/obj/
PRINTFFOLD = ./ft_printf
SRC = ./src
SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	  ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c \
	  ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
	  ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
	  ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	  ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c \
	  ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
	  ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
	  ft_strjoin.c ft_strjoin_fr_frst.c ft_strtrim.c ft_strsplit.c \
	  ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
	  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	  ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
	  ft_lstmap.c ft_print_strtab.c ft_arraymax.c ft_arraymin.c \
	  ft_sortarr_asc.c ft_sortarr_desc.c ft_swap.c \
	  ft_printhex.c ft_putnbr_base.c ft_convert_base.c ft_atoi_base.c \
	  ft_div_mod.c ft_srch_arrelem.c ft_arrrev.c ft_arrnew.c ft_putarr.c \
	  get_next_line.c

OBJ = $(addprefix $(OBJFOLD),$(patsubst %.c, %.o, $(SRCDIR)$(SRC)))
PRINTFOBJ = ./ft_printf/obj/*.o

all:				$(NAME)

$(NAME):			$(OBJ)
	@make -C $(PRINTFFOLD) -f Makefile
	@ar rc $(NAME) $(OBJ) $(PRINTFOBJ)
	@ranlib $(NAME)
	@echo "Libft: done"

$(OBJFOLD)%.o:
	@mkdir -p $(OBJFOLD)
	@$(CC) $(CFLAGS) $(HEADER) -c $(patsubst src/obj/%.o,src/%.c, $@) -o $@


clean:
	@make -C $(PRINTFFOLD) -f Makefile clean
	@rm -rf $(OBJFOLD)

fclean:				clean
	@make -C $(PRINTFFOLD) -f Makefile fclean
	@rm -f $(NAME)

re:					fclean all
