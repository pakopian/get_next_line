/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pakopian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:07:15 by pakopian          #+#    #+#             */
/*   Updated: 2025/04/01 20:07:23 by pakopian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

#include <stdlib.h>
#include <unistd.h>

char    *get_next_line(int fd);
char    *get_line(char  *saved);
char    *update_saved(char *saved);
size_t	ft_strlen(const	char *str);
char	*ft_strchr(const char *s, int c);
char    *ft_strdup(const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);

# endif