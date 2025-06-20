/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:40:45 by mcygan            #+#    #+#             */
/*   Updated: 2025/06/03 11:59:06 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	**get_map(int fd)
{
	int		i;
	char	*line;
	char	**map;

	map = malloc(sizeof(char *) * (MAP_MAX + 1));
	if (!map)
		return (NULL);
	line = next_nonempty_line(fd);
	i = 0;
	while (line && *line != '\n' && i < MAP_MAX)
	{
		map[i] = malloc(sizeof(char) * (MAP_MAX + 1));
		if (!map[i] || copy_line(line, map[i++]))
			return (free_str_array(map), NULL);
		free(line);
		line = get_next_line(fd);
	}
	map[i] = 0;
	if (line || i == MAP_MAX)
		return (free(line), free_str_array(map), NULL);
	return (free(line), map);
}

void	set_map_size(t_data *data)
{
	int		width;
	int		i;
	int		j;

	width = 0;
	i = -1;
	while (data->map[++i])
	{
		j = 0;
		while (data->map[i][j])
			j++;
		if (j > width)
			width = j;
	}
	data->map_w = width;
	data->map_h = i;
	data->map_scale = MINIMAP_SCALE / fmax(width, i);
}

static int	set_player_pos(t_data *data, int x, int y, char dir)
{
	if (data->pos_x > 0.0)
		return (1);
	data->pos_x = x + 0.5001;
	data->pos_y = y + 0.5001;
	if (dir == 'N')
		data->pos_a = -M_PI / 2;
	else if (dir == 'S')
		data->pos_a = M_PI / 2;
	else if (dir == 'W')
		data->pos_a = M_PI;
	else if (dir == 'E')
		data->pos_a = 0;
	return (0);
}

static void	propagate(t_data *data, int x, int y)
{
	if (x > 0 && !data->map_check[y][x - 1])
		parse_cluster(data, x - 1, y);
	if (x < data->map_w - 1 && !data->map_check[y][x + 1])
		parse_cluster(data, x + 1, y);
	if (y > 0 && !data->map_check[y - 1][x])
		parse_cluster(data, x, y - 1);
	if (y < data->map_h - 1 && !data->map_check[y + 1][x])
		parse_cluster(data, x, y + 1);
}

int	parse_cluster(t_data *data, int x, int y)
{
	char	c;

	c = data->map[y][x];
	if (c == '1')
		return (0);
	else if (x == 0 || x == data->map_w - 1 || y == 0 || y == data->map_h - 1)
		return (data->error++, 1);
	else if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (c != '0')
		{
			if (set_player_pos(data, x, y, c))
				return (data->error++, 1);
		}
		data->map_check[y][x] = 1;
		propagate(data, x, y);
	}
	else
		return (data->error++, 1);
	return (0);
}
