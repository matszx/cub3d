/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:21:45 by mcygan            #+#    #+#             */
/*   Updated: 2025/02/12 14:39:04 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	pxl_put(t_img *img, int x, int y, int colour)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)dst = colour;
}

void	draw_tile(t_img *img, int x, int y, int colour)
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

void	draw_player(t_data *data)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = data->player_x * MAP_SCALE - MAP_SCALE / 5;
	y = data->player_y * MAP_SCALE - MAP_SCALE / 5;
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
