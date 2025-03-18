CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = ../libs/libftprintf.a
SRC = ft_printf.c ft_putchar.c ft_putnbrhex.c ft_putunsigned.c \
	ft_putaddres.c ft_putnbr.c ft_putstr.c conversions.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@ar rcs $(NAME) $(OBJ)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean