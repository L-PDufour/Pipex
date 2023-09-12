NAME = pipex
NAME_B = pipex_bonus

SRC			=	pipex.c
OBJ			=	$(SRC:.c=.o)

# SRC_B		=	pipex_bonus.c
# OBJ_B		=	$(SRC_B:.c=.o)

LIBFT		=	libft/libft.a

CC			=	cc
CFLAGS		=	
# -Wall -Wextra -Werror -g

$(NAME): $(OBJ)
		cd libft && make
		$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)

# bonus:	$(OBJ_B)
		# cd libft && make
		# $(CC) $(CFLAGS) $(SRC_B) $(LIBFT) -o $(NAME_B)

all:	$(NAME)

clean:	
		cd libft && make clean
		rm -f $(OBJ) $(OBJ_B)

fclean:	clean
		cd libft && make fclean
		rm -f $(NAME) $(NAME_B)

re:		fclean all

.PHONY: all clean fclean bonus
