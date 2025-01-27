/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:21:45 by mcygan            #+#    #+#             */
/*   Updated: 2025/01/27 14:06:36 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	pxl_put(t_img *img, uint32_t x, uint32_t y, uint32_t colour)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(uint32_t *)dst = colour;
}

void	draw_tile(t_img *img, uint32_t x, uint32_t y, uint32_t colour)
{
	uint32_t	i;
	uint32_t	j;

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

void	draw_player(t_img *img, float x, float y)
{
	uint32_t	i;
	uint32_t	j;

	x *= MAP_SCALE;
	y *= MAP_SCALE;
	x -= 2;
	y -= 2;
	i = (uint32_t)(y);
	while (i < y + 5 && i < WIN_H)
	{
		j = (uint32_t)x;
		while (j < x + 5 && j < WIN_W)
		{
			pxl_put(img, j, i, 0xFF0000);
			j++;
		}
		i++;
	}
}
