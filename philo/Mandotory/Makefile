NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread
SRC = main.c\
	threads.c\
	error_handle.c\
	threads_utils.c\
	threads_utils2.c

OBJS = $(SRC:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS)  -o $(NAME)
	
clean :
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all