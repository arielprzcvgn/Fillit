# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ariperez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 15:40:21 by ariperez          #+#    #+#              #
#    Updated: 2019/01/17 16:00:54 by ariperez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =   fillit

SRCS    =   file_it.c solviminos.c

OBJS	=	$(SRCS:.c=.o)

HDR		=	fillit.h

LIB		=	libft/libft.a

FLAGS   =   -Wall -Werror -Wextra


all:    $(NAME)

$(NAME):
	gcc -c $(FLAGS) $(SRCS)
	make -C libft/ re
	gcc $(OBJS) $(LIB) -o $(NAME)	

clean:
	rm -f $(OBJS)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re:     fclean all

norme:
	norminette $(SRCS) $(HDR)

new:
	python3 gen_tetri.py 0
