# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amichak <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/23 11:53:43 by amichak           #+#    #+#              #
#    Updated: 2018/01/23 12:07:30 by amichak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:		all clean fclean re $(NAME)

CFLAGS = -Wall -Wextra -Werror
SRC = main.c
NAME = ft_ls
OBJFOLD = obj
LIBFT = ./libft/
LIB = -L. libft/libft.a
HEADER = -I ./

OBJ = $(addprefix $(OBJFOLD),$(patsubst %.c, %.o, $(SRC)))

all:		$(NAME)

$(NAME):	$(OBJ)
	@make -C $(LIBFT) -f Makefile
	gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)

$(OBJFOLD)%.o:	%.c
	mkdir -p $(OBJFOLD)
	gcc $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@make -C $(LIBFT) -f Makefile clean
	@rm -rf $(OBJFOLD)

fclean:		clean
	@make -C $(LIBFT) -f Makefile fclean
	@rm -f $(NAME)

re:			fclean all
