NAME = philosophers

FLAG = -Wall -Werror -Wextra

LIB = -lpthread

SRC = main.c exit.c init.c lifecycle.c utils.c utils2.c

OBJ = $(SRC:%.c=%.o)

B_SRC = main_bonus.c routinies_bonus.c utils2_bonus.c utils_bonus.c init_bonus.c exit_bonus.c

B_OBJ = $(B_SRC:%.c=%.o)

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJ) philosophers.h
	gcc $(FLAG) $(OBJ) -o $(NAME) $(LIB)

%.o: %.c
	gcc $(FLAG) -c $< -o $@

bonus: $(B_OBJ) philosophers_bonus.h
	gcc $(FLAG) $(B_OBJ) $(LIB) -o philosophers_bonus

clean:
	rm -f $(OBJ) $(B_OBJ)

fclean: clean
	rm -f $(NAME) philosophers_bonus

re: fclean all