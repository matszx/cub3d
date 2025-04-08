/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:14:01 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/08 15:01:19 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	*next_nonempty_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (*line == 10)
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
	while (src[i] && src[i] != 10 && i < CONFIG_MAX - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (src[i] && src[i] != 10)
		return (1);
	dst[i] = 0;
	return (0);
}

char	**get_grid(int fd)
{
	char	**grid;
	char	*line;
	int		i;

	grid = malloc(sizeof(char *) * CONFIG_MAX);
	if (!grid)
		return (NULL);
	line = next_nonempty_line(fd);
	i = -1;
	while (++i < CONFIG_MAX - 1 && line && *line != 10)
	{
		grid[i] = malloc(sizeof(char) * CONFIG_MAX);
		if (!grid[i] || copy_line(line, grid[i]))
			return (free_split(grid), NULL);
		free(line);
		line = get_next_line(fd);
	}
	grid[i] = 0;
	if (line)
	{
		free(line);
		line = next_nonempty_line(fd);
		if (line)
			return (free_split(grid), NULL);
	}
	return (grid);
}
