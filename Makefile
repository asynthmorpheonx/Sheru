SRC= heap_controller/g_container.c heap_controller/managment_utils.c minishell.c mini_exc/b_utils1.c\
	mini_exc/builtin2.c mini_exc/builtins.c mini_exc/execution.c mini_exc/execution1.c mini_exc/execution2.c\
	mini_exc/pipline.c mini_exc/utils.c mini_exc/export_helpers.c make_nd_store_env.c quote_utils.c\
	store_data_process.c redirections_handle.c tokenize_utils.c handle_cmd_flage.c advanced_split.c prompt_gen.c\
	expansion_handle.c mask_creation.c mini_exc/utils2.c ft_cd_handler.c uns_exp_exit.c ft_export_handler.c
#export_advanced.c  
OBJ= $(SRC:%.c=%.o)
NAME= minishell
LIBS= libs/libft.a
CC= cc
CFLAGS= -Wall -Werror -Wextra -ggdb

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(OBJ) -Llibs -lft -lreadline -o $(NAME)

%.o: %.c
	$(CC) -I includes $(CFLAGS) -c $< -o $@

$(LIBS):
	mkdir -p libs
	make -C libft bonus

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(LIBS) libs $(NAME)

re: fclean all

.PHONY: all re clean fclean

.SECONDARY: $(OBJ)