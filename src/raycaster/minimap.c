/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:06:38 by mcygan            #+#    #+#             */
/*   Updated: 2025/03/17 18:46:35 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	draw_tile(t_img *img, int x, int y, int colour)
{
	int	i;
	int	j;

	x *= MAP_SCALE;
	y *= MAP_SCALE;
	i = y;
	while (i < y + MAP_SCALE && i < WIN_H)
	{
		j = x;
		while (j < x + MAP_SCALE && j < WIN_W)
		{
			pxl_put(img, j, i, colour);
			j++;
		}
		i++;
	}
}

static void	draw_maze(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->grid_h)
	{
		j = -1;
		while (++j < data->grid_w)
		{
			if (data->map[i][j] == '1')
				draw_tile(&data->img, j, i, 0x151515);
			else
				draw_tile(&data->img, j, i, 0x065EE2);
		}
	}
}

static void	draw_player(t_data *data)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = data->pos_x * MAP_SCALE - MAP_SCALE / 5;
	y = data->pos_y * MAP_SCALE - MAP_SCALE / 5;
	i = y;
	if (i < 0)
		i = 0;
	while (i < y + 5 && i < WIN_H)
	{
		j = x;
		if (j < 0)
			j = 0;
		while (j < x + 5 && j < WIN_W)
		{
			pxl_put(&data->img, j, i, 0xFF0000);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	draw_maze(data);
	draw_player(data);
}
