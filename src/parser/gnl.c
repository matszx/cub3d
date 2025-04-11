/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:28:55 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/11 23:35:25 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	*truncate_buffer(char *buffer)
{
	
	char	*nl;
	size_t	nl_idx;
	int		i;
	char	*new;

	nl = ft_strchr(buffer, 10);
	if (!nl)
		return (free(buffer), NULL);
	nl_idx = nl - buffer;
	new = malloc(ft_strlen(buffer) - nl_idx + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (buffer[++nl_idx])
		new[i++] = buffer[nl_idx];
	new[i] = 0;
	return (free(buffer), new);
}

static char	*get_line(char *buffer)
{
	char	*eol;
	size_t	eol_idx;
	char	*line;

	if (!*buffer)
		return (NULL);
	eol = ft_strchr(buffer, 10);
	if (eol)
		eol_idx = eol - buffer + 1;
	else
		eol_idx = ft_strlen(buffer);
	line = malloc(eol_idx + 1);
	if (!line)
		return (NULL);
	line[eol_idx] = 0;
	while (eol_idx--)
		line[eol_idx] = buffer[eol_idx];
	return (line);
}

static char	*join_buffer(char *buffer, char *buf)
{
	char	*res;

	res = ft_strjoin(buffer, buf);
	return (free(buffer), res);
}

static char	*get_buffer(int fd, char *buffer)
{
	char	*buf;
	int		bytes_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(buf), NULL);
		buf[bytes_read] = 0;
		buffer = join_buffer(buffer, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (free(buf), buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	buffer = get_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = truncate_buffer(buffer);
	return (line);
}
