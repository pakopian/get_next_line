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

char    *get_line(char  *saved)
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

char    *update_saved(char *saved)
{
    char	*new_saved;
	int		i;
	int		j;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	new_saved = (char *)malloc(ft_strlen(saved) - i);
	if (!new_saved)
		return (NULL);
	j = 0;
	i++;
	while (saved[i])
		new_saved[j++] = saved[i++];
	new_saved[j] = '\0';
	free(saved);
	return (new_saved);
}

char	*read_and_save(int fd, char *saved)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(saved, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		if (bytes_read == 0)
			break;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(saved, buffer);
		free(saved);
		saved = temp;
	}
	free(buffer);
	return (saved);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	
	saved = read_and_save(fd, saved);
	if (!saved)
		return (NULL);

	line = get_line(saved);
	saved = update_saved(saved);

	return (line);
}
