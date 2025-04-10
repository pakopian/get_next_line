/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pakopian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:07:00 by pakopian          #+#    #+#             */
/*   Updated: 2025/04/01 20:07:08 by pakopian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *saved)
{
	int		i;
	char	*text;

	if (!saved || !*saved)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (saved[i] == '\n')
		i++;
	text = (char *)malloc(i + 1);
	if (!text)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
	{
		text[i] = saved[i];
		i++;
	}
	if (saved[i] == '\n')
		text[i++] = '\n';
	text[i] = '\0';
	return (text);
}

static char	*update_saved(char *saved)
{
	char	*new_saved;
	int		i;

	if (!saved)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
		return (free(saved), NULL);
	i++;
	if (!saved[i])
		return (free(saved), NULL);
	new_saved = ft_strdup(saved + i);
	free(saved);
	return (new_saved);
}

static char	*read_and_save(int fd, char *saved)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!saved)
		saved = ft_strdup("");
	if (!saved)
		return (free(buffer), NULL);
	while (!ft_strchr(saved, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(saved), free(buffer), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(saved, buffer);
		if (!temp)
			return (free(saved), free(buffer), NULL);
		free(saved);
		saved = temp;
	}
	free(buffer);
	if (!*saved)
		return (free(saved), NULL);
	return (saved);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(saved);
		return (NULL);
	}
	saved = read_and_save(fd, saved);
	if (!saved)
		return (saved = NULL, NULL);
	line = get_line(saved);
	if (!line)
		return (free(saved), saved = NULL, NULL);
	return (saved = update_saved(saved), line);
}
