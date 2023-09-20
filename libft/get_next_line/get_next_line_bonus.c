/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <leon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 09:49:41 by leon              #+#    #+#             */
/*   Updated: 2023/04/09 12:41:16 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_line(char *str)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str[0])
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (ft_free(&line));
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		line[j++] = str[i++];
	if (str[i] == '\n')
		line[j++] = str[i++];
	line[j] = 0;
	return (line);
}

char	*fill_stash(char *stash, int fd)
{
	char	*buffer;
	int		read_bytes;

	read_bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&stash));
	buffer[0] = 0;
	while (read_bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes > 0)
		{
			buffer[read_bytes] = 0;
			stash = ft_strjoin(stash, buffer);
		}
	}
	free(buffer);
	if (read_bytes == -1)
		return (ft_free(&stash));
	return (stash);
}

char	*clean_stash(char *str)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (ft_free(&str));
	new_stash = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!new_stash)
		return (ft_free(&str));
	i++;
	j = 0;
	while (str[i])
		new_stash[j++] = str[i++];
	new_stash[j] = 0;
	free(str);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[1023];

	line = NULL;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = fill_stash(stash[fd], fd);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	if (!line)
		return (ft_free(&stash[fd]));
	stash[fd] = clean_stash(stash[fd]);
	return (line);
}
