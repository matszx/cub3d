/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:14:01 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/09 20:16:39 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*next_nonempty_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && *line == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

static int	copy_line(char *src, char *dst)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '\n' && i < CONFIG_MAX)
	{
		dst[i] = src[i];
		i++;
	}
	if (src[i] && src[i] != '\n')
		return (1);
	dst[i] = 0;
	return (0);
}

char	**get_map(int fd)
{
	int		i;
	char	*line;
	char	**map;

	map = malloc(sizeof(char *) * (CONFIG_MAX + 1));
	if (!map)
		return (NULL);
	line = next_nonempty_line(fd);
	i = 0;
	while (line && *line != 10 && i < CONFIG_MAX)
	{
		map[i] = malloc(sizeof(char) * (CONFIG_MAX + 1));
		if (!map[i] || copy_line(line, map[i++]))
			return (free_split(map), NULL);
		free(line);
		line = get_next_line(fd);
	}
	map[i] = 0;
	if (line || i == CONFIG_MAX)
		return (free(line), free_split(map), NULL);
	return (free(line), map);
}
