NAME = philo_bonus
CFLAGS = -Wall -Wextra -Werror -pthread
SRC = 	main_bonus.c\
		process.c\
		process_utils.c

OBJS = $(SRC:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)  -o $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all