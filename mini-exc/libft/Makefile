CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs
NAME = ../libft.a
SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c\
	  ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c\
	  ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c\
	  ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c\
	  ft_strrchr.c ft_tolower.c ft_toupper.c ft_itoa.c ft_putchar_fd.c\
	  ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_substr.c\
	  ft_striteri.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_strcpy.c\
	  ft_strcat.c ft_strcmp.c

SRCBONUS = ft_lstadd_front_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c\
		   ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c\
		   ft_lstmap_bonus.c get_next_line.c get_next_line_utils.c get_helper.c
OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(SRCBONUS:.c=.o)

all: $(NAME)
bonus: $(OBJ) $(BONUS_OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ) $(BONUS_OBJ)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
