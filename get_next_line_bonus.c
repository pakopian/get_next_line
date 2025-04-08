/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pakopian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:24:55 by pakopian          #+#    #+#             */
/*   Updated: 2025/04/08 21:24:59 by pakopian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_line(char *saved)
{
	int		i;
	char	*text;

	if (!saved || !*saved)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	text = (char *)malloc(i + 2);
	if (!text)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
	{
		text[i] = saved[i];
		i++;
	}
	if (saved[i] == '\n')
	{
		text[i] = '\n';
		i++;
	}
	text[i] = '\0';
	return (text);
}

static char	*update_saved(char *saved)
{
	char	*new_saved;
	int		i;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
		return (free(saved), NULL);
	new_saved = ft_strdup(saved + i + 1);
	free(saved);
	return (new_saved);
}

static char	*read_and_save(int fd, char *saved)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		bytes_read;

	if (!saved)
		saved = ft_strdup("");
	while (!ft_strchr(saved, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(saved), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(saved, buffer);
		if (!temp)
			return (free(saved), NULL);
		free(saved);
		saved = temp;
	}
	if (!*saved)
		return (free(saved), NULL);
	return (saved);
}

char	*get_next_line(int fd)
{
	static char	*saved[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved[fd] = read_and_save(fd, saved[fd]);
	if (!saved[fd])
		return (NULL);
	if (!*saved[fd])
		return (free(saved[fd]), saved[fd] = NULL, NULL);
	line = get_line(saved[fd]);
	if (!line)
		return (free(saved[fd]), saved[fd] = NULL, NULL);
	saved[fd] = update_saved(saved[fd]);
	return (line);
}
