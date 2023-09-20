NAME = libft.a

RM = rm -f

CFLAGS =  -Wall -Wextra -Werror -g

CC = gcc

GNL = get_next_line/

.PHONY: all clean fclean re bonus

SRC = ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strcat.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \

SRC_BONUS = ft_lstnew.c \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstsize.c \

OBJ = $(SRC:.c=.o)

GNL_OBJS = $(GNL)get_next_line.o \
	$(GNL)get_next_line_utils.o \

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: gnl $(NAME)

gnl:
	@$(MAKE) -C $(GNL)

$(NAME) : $(OBJ)
	@ar rcs $(NAME) $(OBJ) $(GNL_OBJS)

bonus: $(OBJ_BONUS)
	@ar rcs $(NAME) $(OBJ_BONUS)

clean:
	@$(RM) $(OBJ) $(OBJ_BONUS)
	@$(MAKE) -C $(GNL) fclean
fclean: clean
	@$(RM) $(NAME) 


re: fclean all



