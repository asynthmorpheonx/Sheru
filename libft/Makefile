CC = cc
SRC =ft_atoi.c ft_isalnum.c ft_isdigit.c ft_memchr.c ft_memcpy.c ft_memset.c ft_putendl_fd.c ft_putstr_fd.c ft_strcat.c\
	ft_strcmp.c ft_strdup.c ft_strjoin.c ft_strlcpy.c ft_strncmp.c ft_substr.c ft_bzero.c ft_isalpha.c ft_itoa.c ft_memcmp.c\
	ft_memmove.c ft_putchar_fd.c ft_putnbr_fd.c ft_split.c ft_strchr.c ft_strcpy.c ft_striteri.c ft_strlcat.c ft_strlen.c\
	ft_strrchr.c get_next_line.c
OBJ = ${SRC:.c=.o}
CFLAGS = -Wall -Werror -Wextra
NAME = ../libs/libft.a

all : $(NAME)

re : fclean all

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o : %.c
	$(CC) -I../includes $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ) $(BOBJ)

fclean : clean
	rm -f $(NAME)

.PHONY: all re clean fclean bonus