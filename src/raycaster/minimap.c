/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:06:38 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/28 01:11:06 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	draw_tile(t_data *data, int x, int y, int colour)
{
	int	i;
	int	j;

	x *= data->map_scale;
	y *= data->map_scale;
	i = y;
	while (i < y + data->map_scale && i < WIN_H)
	{
		j = x;
		while (j < x + data->map_scale && j < WIN_W)
			pxl_put(&data->img, j++, i, colour);
		i++;
	}
}

static void	draw_maze(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map_h)
	{
		j = -1;
		while (++j < data->map_w)
		{
			if (data->map[i][j] == '0'\
				|| data->map[i][j] == 'N' || data->map[i][j] == 'S'\
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
				draw_tile(data, j, i, 0x065EE2);
			else
				draw_tile(data, j, i, 0x151515);
		}
	}
}

static void	draw_player(t_data *data)
{
	int	player_size;
	int	x;
	int	y;
	int	i;
	int	j;

	player_size = data->map_scale / 2;
	x = data->pos_x * data->map_scale - data->map_scale / player_size;
	y = data->pos_y * data->map_scale - data->map_scale / player_size;
	i = y;
	if (i < 0)
		i = 0;
	while (i < y + player_size && i < WIN_H)
	{
		j = x;
		if (j < 0)
			j = 0;
		while (j < x + player_size && j < WIN_W)
			pxl_put(&data->img, j++, i, 0xFF0000);
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	draw_maze(data);
	draw_player(data);
}
