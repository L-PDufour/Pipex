# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldufour </var/spool/mail/ldufour>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 13:36:35 by ldufour           #+#    #+#              #
#    Updated: 2023/09/18 15:26:47 by ldufour          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Pipex
NAME_B = pipex_bonus

SRC = src/pipex.c \
	src/utils.c  

OBJ = $(SRC:.c=.o)

LIBFT =	libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

$(NAME): $(OBJ)
		cd libft && make
		$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)

all:	$(NAME)

clean:	
		cd libft && make clean
		rm -f $(OBJ) $(OBJ_B)

fclean:	clean
		cd libft && make fclean
		rm -f $(NAME) $(NAME_B)

re:		fclean all

.PHONY: all clean fclean bonus
