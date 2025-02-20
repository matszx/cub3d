/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:42:11 by mcygan            #+#    #+#             */
/*   Updated: 2025/02/20 17:47:38 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <mlx.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define KEY_W			0x77
#define KEY_A			0x61
#define KEY_S			0x73
#define KEY_D			0x64
#define KEY_LEFT		0xff51
#define KEY_RIGHT		0xff53
#define KEY_ESCAPE		0xff1b

#define WIN_W			1200
#define WIN_H			800
#define MAP_W			16
#define MAP_H			16
#define MAP_SCALE		10
#define FOV				60
#define MOVE_SPEED		0.03

typedef struct s_img
{
	void	*ptr;
	char	*addr;

	int		bpp;
	int		line_len;
	int		endian;

	int		w;
	int		h;
}	t_img, t_texture;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;

	char	**map;
	int		map_w;
	int		map_h;

	double	pos_x;
	double	pos_y;
	double	pos_a;
	double	fov;

	bool	w_press;
	bool	a_press;
	bool	s_press;
	bool	d_press;
	bool	left_press;
	bool	right_press;

	size_t	last_frame_time;

	t_texture	texture;
	int			side;
	double		wallX;
	double		wallY;
	double		rayDirX;
	double		rayDirY;
	int			tex_x;
	int			tex_y;
}	t_data;

typedef struct s_render_info
{
	
}	t_render_info;


// init.c
void	init_data(t_data *data, char **map);

// minimap.c
void	draw_minimap(t_data *data);

// render.c
int		render(t_data *data);

// move.c
void	player_move(t_data *data);

// handlers.c
int		close_handler(t_data *data, char *error);
void	init_events(t_data *data);

// utils.c
size_t	time_ms(void);
void	pxl_put(t_img *img, int x, int y, int colour);
