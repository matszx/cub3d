/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:21:45 by mcygan            #+#    #+#             */
/*   Updated: 2025/01/24 10:42:19 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

uint32_t	colour(uint8_t r, uint8_t g, uint8_t b)
{
	return (r << 16 | g << 8 | b);
}

uint32_t	to_colour(t_vec v)
{
	return (colour(v.x * 255, v.y * 255, v.z * 255));
}

void	pxl_put(t_img *data, uint32_t x, uint32_t y, uint32_t colour)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = colour;
}

void	draw_tile(t_img *data, uint32_t x, uint32_t y, uint32_t colour)
{
	uint32_t	i;
	uint32_t	j;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = y;
	while (i < y + TILE_SIZE && i < HEIGHT)
	{
		j = x;
		while (j < x + TILE_SIZE && j < WIDTH)
		{
			pxl_put(data, j, i, colour);
			j++;
		}
		i++;
	}
}

void	draw_player(t_img *data, float x, float y)
{
	uint32_t	i;
	uint32_t	j;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = (uint32_t)(y);
	while (i < y + 5 && i < HEIGHT)
	{
		j = (uint32_t)x;
		while (j < x + 5 && j < WIDTH)
		{
			pxl_put(data, j, i, 0xFFFFFF);
			j++;
		}
		i++;
	}
}
