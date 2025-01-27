/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:42:11 by mcygan            #+#    #+#             */
/*   Updated: 2025/01/27 14:04:26 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <mlx.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define WIN_W		800
#define WIN_H		800
#define MAP_W		16
#define MAP_H		16
#define MAP_SCALE	10
#define FOV			60

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

// utils.c
void		pxl_put(t_img *img, uint32_t x, uint32_t y, uint32_t colour);
void		draw_tile(t_img *img, uint32_t x, uint32_t y, uint32_t colour);
void		draw_player(t_img *img, float x, float y);
