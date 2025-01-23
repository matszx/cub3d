/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:42:11 by mcygan            #+#    #+#             */
/*   Updated: 2025/01/23 18:39:26 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <mlx.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>

#define WIDTH		1024
#define HEIGHT		768
#define TILE_SIZE	20

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef t_vec	t_point;
typedef t_vec	t_colour;

typedef struct s_ray
{
	t_point	origin;
	t_vec	dir;
}	t_ray;

// utils.c
uint32_t	colour(uint8_t a, uint8_t r, uint8_t g, uint8_t b);
uint32_t	to_colour(t_vec v);
void		pxl_put(t_img *data, uint32_t x, uint32_t y, uint32_t colour);
void		draw_tile(t_img *data, uint32_t x, uint32_t y, uint32_t colour);
