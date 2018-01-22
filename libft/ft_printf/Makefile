# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amichak <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/11 13:15:45 by amichak           #+#    #+#              #
#    Updated: 2017/12/05 16:43:12 by amichak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:				all clean fclean re $(NAME)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
HEADER = -I ./
OBJFOLD = ./obj/
SRC = ft_printf.c chars.c ft_convert_base_printf.c ft_putchar.c \
	  ft_putstr.c ft_strlen_printf.c ft_memdel.c ft_strncat_pf.c ft_strnew.c \
	  ft_memset.c ft_putnbr_pf.c ft_strdel.c modificators.c ft_strchr.c \
	  ft_atoi_printf.c colors.c ft_strcmp_pf.c handlers.c padding.c \
	  print_chars.c print_num.c redirect_print.c print_float.c

OBJ = $(addprefix $(OBJFOLD),$(patsubst %.c, %.o, $(SRC)))

all:				$(NAME)

$(NAME):			$(OBJ)
	
$(OBJFOLD)%.o: 		%.c
	@mkdir -p $(OBJFOLD)
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@rm -rf $(OBJFOLD)

fclean:				clean
	@rm -f $(NAME)

re:					fclean all
