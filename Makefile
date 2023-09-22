# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldufour <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 13:31:48 by ldufour           #+#    #+#              #
#    Updated: 2023/09/19 13:32:20 by ldufour          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAMEB = pipex_bonus

SRC = src/pipex.c \
	src/utils.c  

OBJ = $(SRC:.c=.o)

SRCB = bonus/pipex_bonus.c \
	bonus/bonus_utils.c \
	src/utils.c
	
OBJB = $(SRCB:c=o)

LIBFT =	libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

$(NAME): $(OBJ)
		cd libft && make
		$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)

bonus:	$(OBJB)
		cd libft && make
		$(CC) $(CFLAGS) $(SRCB) $(LIBFT) -o $(NAMEB)

all:	$(NAME)

clean:	
		cd libft && make clean
		rm -f $(OBJ) $(OBJB)

fclean:	clean
		cd libft && make fclean
		rm -f $(NAME) $(NAMEB)

re:		fclean all

.PHONY: all clean fclean 
