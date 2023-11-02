/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:46:29 by aducobu           #+#    #+#             */
/*   Updated: 2023/05/27 02:04:58 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_strlen(const char *s);
void				*ft_memset(void *b, int c, int len);
void				ft_bzero(void *s, int n);
void				*ft_memcpy(void *dst, const void *src, int n);
void				*ft_memmove(void *dst, const void *src, int len);
int					ft_strlcpy(char *dst, const char *src, int dstsize);
int					ft_strlcat(char *dst, const char *src, int dstsize);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, int n);
void				*ft_memchr(const void *s, int c, int n);
int					ft_memcmp(const void *s1, const void *s2, int n);
char				*ft_strnstr(const char *haystack, const char *needle,
						int len);
int					ft_atoi(const char *str);
long int			ft_long_atoi(const char *str);
void				*ft_calloc(int count, int size);
char				*ft_strdup(const char *s1);

char				*ft_substr(char const *s, unsigned int start, int len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putstr(char *s);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

int					is_an_option(char c);
int					conversion(va_list args, char c);
int					ft_printf(const char *format, ...);
int					ft_putchar(char c);
int					ft_putstr_len(char *str);
int					ft_num_len(unsigned int num);
char				*ft_unsigned_itoa(unsigned int nb);
int					ft_print_unsigned(unsigned int nb);
int					ft_print_ptr(unsigned long p);
int					size_nb(int nb);
char				*ft_itoa(int nb);
int					ft_print_nbr(int nb);
int					size_nb_hexa(unsigned int nb);
void				ft_print_hexa(unsigned int nb, char c);
int					convert_hexa(unsigned int nb, char c);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char				*get_next_line(int fd);
char				*clean_stash(char *stash);
void				modif_stash(char *stash);
int					is_new_line(char *line);
char				*just_the_line(char str[]);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif