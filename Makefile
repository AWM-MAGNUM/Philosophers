NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror  -fsanitize=thread

OBJ = descartes_philo.c\
	rousseau_philo.c\
	socrate_philo.c \
	kant_philo.c

	
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	
re: fclean all

clean:
	rm -f $(NAME)
	
fclean:clean
