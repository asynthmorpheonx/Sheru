SRC= heap_controller/g_container.c heap_controller/managment_utils.c minishell.c make_nd_store_env.c\
	quote_utils.c store_data_process.c redirections_handle.c tokenize_utils.c handle_cmd_flage.c\
	advanced_split.c prompt_gen.c expansion_handle.c mask_creation.c
OBJ= $(SRC:%.c=%.o)
NAME= minishell
LIBS= libs/libft.a libs/libftprintf.a
CC= cc
CFLAGS= -Wall -Werror -Wextra -g3

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