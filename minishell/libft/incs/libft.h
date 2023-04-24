/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:38:22 by xcharra           #+#    #+#             */
/*   Updated: 2023/03/16 18:52:14 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

/* Character functions */
int		ft_isascii(int c);

int		ft_isalnum(int c);

int		ft_isalpha(int c);

int		ft_isdigit(int c);

int		ft_isprint(int c);

int		ft_tolower(int c);

int		ft_toupper(int c);

/* Memory fonctions */
void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t count, size_t size);

void	*ft_memchr(const void *mem, int c, size_t n );

int		ft_memcmp(const void *mem1, const void *mem2, size_t size);

void	*ft_memcpy(void *mdst, const void *msrc, size_t n);

void	*ft_memmove(void *mdst, const void *msrc, size_t n);

void	*ft_memset(void *mem, int v, size_t n);

/* String functions */
int		ft_atoi(const char *nbr);

char	*ft_itoa(int n);
/* Precision 15 max */
char	*ft_dtoa(double n, size_t precision);

char	**ft_split(char const *s, char c);

char	*ft_strchr(const char *str, int c);

char	*ft_strdup(const char *src);

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

char	*ft_strjoin(char const *s1, char const *s2);

size_t	ft_strlcat(char *dst, const char *src, size_t n);

size_t	ft_strlcpy(char *dst, const char *src, size_t n);

size_t	ft_strlen(const char *str);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strnstr(const char *str, const char *to_find, size_t n);

char	*ft_strrchr(const char *str, int c);

char	*ft_strtrim(char const *s1, char const *set);

char	*ft_substr(char const *s, unsigned int start, size_t len);

/* Output fonctions */
void	ft_putchar_fd(char c, int fd);

int		ft_putchar(int c, int fd);

void	ft_putendl_fd(char *s, int fd);

int		ft_putnbr_base(size_t nb, char *base, int fd);

void	ft_putnbr_fd(int nb, int fd);

int		ft_putnbr(int nb, int fd);

void	ft_putstr_fd(char *s, int fd);

int		ft_putstr(char *str, int fd);

int		ft_putunbr(unsigned int nb, int fd);

/* Linked list functions */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void	ft_lstadd_back(t_list **lst, t_list *new);

void	ft_lstadd_front(t_list **lst, t_list *new);

void	ft_lstclear(t_list **lst, void (*del)(void*));

void	ft_lstdelone(t_list *lst, void (*del)(void*));

void	ft_lstiter(t_list *lst, void (*f)(void *));

t_list	*ft_lstlast(t_list *lst);

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_list	*ft_lstnew(void *content);

int		ft_lstsize(t_list *lst);

/* get_next_line */
char	*get_next_line(int fd);

/* ft_printf */
# define HEXAL	"0123456789abcdef"
# define HEXAU	"0123456789ABCDEF"
# define MININT	"-2147483648"

int		ft_fdprintf(int fd, const char *str, ...);

int		ft_printf(const char *str, ...);

#endif
