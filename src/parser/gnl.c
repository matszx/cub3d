/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:28:55 by mcygan            #+#    #+#             */
/*   Updated: 2025/03/17 18:28:56 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	*ft_truncate(char *buffer)
{
	char	*nl;
	size_t	nl_idx;
	char	*new;
	int		i;

	nl = ft_strchr(buffer, '\n');
	if (!nl)
		return (free(buffer), NULL);
	nl_idx = nl - buffer;
	new = malloc(ft_strlen(buffer) - nl_idx + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (buffer[++nl_idx])
		new[i++] = buffer[nl_idx];
	new[i] = '\0';
	return (free(buffer), new);
}

static char	*ft_getline(char *buffer)
{
	char	*eol;
	size_t	eol_idx;
	char	*line;

	if (!*buffer)
		return (NULL);
	eol = ft_strchr(buffer, '\n');
	if (eol)
		eol_idx = eol - buffer + 1;
	else
		eol_idx = ft_strlen(buffer);
	line = malloc(eol_idx + 1);
	if (!line)
		return (NULL);
	line[eol_idx] = '\0';
	while (eol_idx--)
		line[eol_idx] = buffer[eol_idx];
	return (line);
}

static char	*ft_join(char *buffer, char *buf)
{
	char	*res;

	res = ft_strjoin(buffer, buf);
	return (free(buffer), res);
}

static char	*ft_read(int fd, char *buffer)
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
		buf[bytes_read] = '\0';
		buffer = ft_join(buffer, buf);
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
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_getline(buffer);
	buffer = ft_truncate(buffer);
	return (line);
}
