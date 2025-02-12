/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:42:11 by mcygan            #+#    #+#             */
/*   Updated: 2025/02/12 13:27:36 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <mlx.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define WIN_W		800
#define WIN_H		800
#define MAP_W		16
#define MAP_H		16
#define MAP_SCALE	10
#define FOV			60
#define MOVE_SPEED	5

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;

	char	**map;
	int		map_w;
	int		map_h;

	float	player_x;
	float	player_y;
	float	player_a;
	float	fov;
}	t_data;

// utils.c
void	pxl_put(t_img *img, int x, int y, int colour);
void	draw_tile(t_img *img, int x, int y, int colour);
void	draw_player(t_data *data);

// handlers.c
void	events_init(t_data *data);

// move.c
void	move_W(t_data *data);
void	move_A(t_data *data);
void	move_S(t_data *data);
void	move_D(t_data *data);
