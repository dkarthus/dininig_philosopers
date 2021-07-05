NAME = philosophers

FLAG = -Wall -Werror -Wextra

LIB = -lpthread

SRC = main.c exit.c init.c lifecycle.c utils.c

OBJ = $(SRC:%.c=%.o)

B_SRC =

B_OBJ = $(B_SRC:%.c=%.o)

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJ) philosophers.h
	gcc $(FLAG) $(OBJ) $(LIB) -o $(NAME)

%.o: %.c
	gcc $(FLAG) -c $< -o $@

bonus: $(B_OBJ)
	gcc $(FLAG) $(B_OBJ) $(LIB) -o philosophers_bonus

clean:
	rm -f $(OBJ) $(B_OBJ)

fclean: clean
	rm -f $(NAME) philosophers_bonus

re: fclean all