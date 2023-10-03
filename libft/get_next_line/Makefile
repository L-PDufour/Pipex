CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRCS = get_next_line.c \
       get_next_line_utils.c
BONUS_SRCS = $(shell find . -iname "*_bonus.c")
OBJS = $(SRCS:.c=.o)

all : $(OBJS)

%.o : %.c
	@$(CC) $(CFLAGS) -c $(SRCS) -o $(OBJS)

$(OBJS) : 
	@$(CC) $(CFLAGS) -c $(SRCS) 

bonus :
	@$(CC) $(CFLAGS) $(BONUS_SRCS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re : clean all

.PHONY: clean fclean re valgrind all bonus
