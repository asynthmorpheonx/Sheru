SRC= heap_controller/g_container.c heap_controller/managment_utils.c minishell.c split_utils.c
OBJ= $(SRC:%.c=%.o)
NAME= minishell
LIBS= libs/libft.a libs/libftprintf.a
CC= cc
CFLAGS= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(OBJ) -Llibs -lft -lftprintf -lreadline -o $(NAME)

%.o: %.c
	$(CC) -I includes $(CFLAGS) -c $< -o $@

$(LIBS):
	mkdir -p libs
	make -C libft bonus
	make -C ft_printf

clean:
	make -C libft clean
	make -C ft_printf clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	make -C ft_printf fclean
	rm -rf $(LIBS) libs $(NAME)

re: fclean all

.PHONY: all re clean fclean

.SECONDARY: