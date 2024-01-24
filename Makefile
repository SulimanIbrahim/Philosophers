NAME = philo
# CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address -pthread 
CFLAGS = -Wall -Wextra -Werror -g3  -pthread 
RM = rm -rf

SRC = main.c

OBJS = $(SRC:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS)  -o $(NAME)
	
clean :
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all