SRC=
OBJ= $(SRC:%.c=%.o)
NAME= minishell
LIBS= libs/libft.a libs/libftprintf.a
CC= cc
CFLAGS= -Wall -Werror -Wextra
ILFLAGS= 

all: $(NAME)

$(NAME): $(LIBS) $(OBJ)
	$(CC) $(OBJ) -I includes -L libs -lft -lprintf -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBS):
	mkdir libs
	make -C libft bonus
	make -C ft_printf

clean:
	make -C libft clean
	make -C ft_printf clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	make -C ft_printf fclean
	rm -rf $(LIBS)

re: fclean all

.PHONY: all re clean fclean

.SECONDARY: