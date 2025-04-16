/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:21:30 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/03/17 22:15:21 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 1024
/* Memory Functions */
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memmove(void *to, const void *from, size_t len);
void		*ft_memcpy(void *to, const void *from, size_t num_bytes);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
/* String Functions */
char		*ft_strcpy(char *dest, const char *src);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *string, const char *to_find, size_t len);
char		*ft_strdup(const char *s1);
char		*ft_strchr(const char *s, int c);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char		*ft_itoa(int n);
char		**ft_split(const char *s, char c);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strcat(char *dest, const char *src);
/* Additional String Functions */
size_t		ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dest, const char *src, size_t dsize);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
/* Character Functions */
int			ft_isalnum(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_isprint(int c);
int			ft_isdigit(int c);
int			ft_isascii(int c);
int			ft_isalpha(int c);
/* File Descriptor Functions */
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(const char *s, int fd);
void		ft_putendl_fd(const char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
/* Linked List Structure */
typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}		t_list;
/* Linked List Functions */
t_list	*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *ne);
int			ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *ne);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
				void (*del)(void *));
char	*get_next_line(int fd);
t_list	*lastnode(t_list *lst);
int		ft_getn(t_list *lst);
int		lenton(t_list *lst);
void	copy_str(t_list *lst, char *buf);
void	ft_free_gnl(t_list **lst, char *buf, t_list *node);
int		get(char *buff);
int 	ft_strcmp(char *s1, char *s2);
#endif
