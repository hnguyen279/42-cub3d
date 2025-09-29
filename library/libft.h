/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:02:16 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/09/11 15:45:04 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>

typedef unsigned char	t_byte;
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
void	*ft_memset(void *ptr, int value, size_t num);
void	ft_bzero(void *s, size_t len);
void	*ft_memcpy(void *des, const void *src, size_t len);
void	*ft_memmove(void *dest_str, const void *src_str, size_t numBytes);
void	*ft_memchr(const void *str, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);

char	*ft_itoa(int n);
char	*ft_strdup(const char *src);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *small, size_t len);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char c);
char	**ft_copy_2d(char **arr);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_lstadd_front(t_list **lst, t_list *new);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *des, const char *src, size_t sizeOfDes);
size_t	ft_strlcpy(char *des, const char *src, size_t size);
size_t	ft_strspn(const char *s, const char *accept);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isquote(char c);
int		ft_isspace(int c);
int		ft_isoperator(char c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *str);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
int		count_words(char *s, char delimiter);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_free_arr_2d(char **arr);
void	ft_free_arr_3d(char ***arr);
void	ft_free_process_2d(char **arr, size_t current);
void	ft_free_process_3d(char ***arr, size_t current);

int					ft_putchar(char c, int fd);
int					ft_putstr(char *str, int fd);
int					ft_putnbr_base(unsigned long long nbr, const char *base, int fd);
int					ft_putptr(void *ptr, int fd);
int					ft_putnbr(int nbr, int fd);
int					ft_putnbr_unsigned(unsigned int nbr, int fd);
int					ft_printf_fd(int fd, const char *format, ...);


#endif
