/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:21:45 by mcygan            #+#    #+#             */
/*   Updated: 2025/01/23 17:47:37 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

uint32_t	colour(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

uint32_t	to_colour(t_vec v)
{
	return (colour(255, v.x * 255, v.y * 255, v.z * 255));
}

void	pxl_put(t_data *data, uint32_t x, uint32_t y, uint32_t colour)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = colour;
}
