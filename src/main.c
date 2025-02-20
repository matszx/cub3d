/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:30:03 by mcygan            #+#    #+#             */
/*   Updated: 2025/02/20 13:59:24 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static t_texture	init_texture(t_data *data, char *path)
{
	t_texture	texture;

	if (!(texture.ptr = mlx_xpm_file_to_image\
		(data->mlx, path, &texture.w, &texture.h)))
		close_handler(data, "can't load texture");
	if (!(texture.addr = mlx_get_data_addr\
		(texture.ptr, &texture.bpp, &texture.line_len, &texture.endian)))
		close_handler(data, "can't get texture memory addr");
	return (texture);
}

static void	init_data(t_data *data, char **map)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, "cub3d");
	data->img.ptr = mlx_new_image(data->mlx, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(\
		data->img.ptr, &data->img.bpp, &data->img.line_len, &data->img.endian);
	data->map = map;
	data->map_w = 16;
	data->map_h = 16;
	data->player_x = 1.9;
	data->player_y = 1.9;
	data->player_a = 1.5;
	data->fov = M_PI / (180.0 / FOV);
	data->w_press = false;
	data->a_press = false;
	data->s_press = false;
	data->d_press = false;
	data->left_press = false;
	data->right_press = false;
	data->last_frame_time = time_ms();
	data->texture = init_texture(data, "./textures/metal.xpm");
}

static void	draw_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map_h)
	{
		j = -1;
		while (++j < data->map_w)
		{
			if (data->map[i][j] == '1')
				draw_tile(&data->img, j, i, 0x151515);
			else
				draw_tile(&data->img, j, i, 0x065EE2);
		}
	}
}

static int	tex_pxl_colour(t_data *data, int y, int h)
{
	int	texX;
	int	texY;

	texX = data->wallX * data->texture.w;
	if ((data->side && data->rayDirY < 0) || (!data->side && data->rayDirX > 0))
		texX = data->texture.w - texX - 1;
	texY = ((double)y / (double)h) * (double)data->texture.h;
	return (data->texture.addr[data->texture.w * texY + texX]);
}

static void	draw_vertical_ray(t_data *data, int x, int h)
{
	int	ceiling;
	int	floor;
	int	i;

	ceiling = (WIN_H - h) / 2;
	floor = ceiling + h;
	if (floor > WIN_H)
		floor = WIN_H;
	if (x < MAP_W * MAP_SCALE)
		i = MAP_H * MAP_SCALE - 1;
	else
		i = -1;
	while (++i < ceiling)
		pxl_put(&data->img, x, i, 0x99DDFF);
	while (++i < floor)
		pxl_put(&data->img, x, i, tex_pxl_colour(data, i - ceiling, h));
	while (++i < WIN_H)
		pxl_put(&data->img, x, i, 0x2F1600);
}

static double	dda(t_data *data, double cx, double cy)
{
	double	posX = data->player_x;
	double	posY = data->player_y;
	double	rayDirX = cx - posX;
	double	rayDirY = cy - posY;
	double	deltaDistX;
	double	deltaDistY;
	int		mapX = (int)posX;
	int		mapY = (int)posY;
	double	sideDistX;
	double	sideDistY;
	int		stepX;
	int		stepY;
	bool	hit = false;
	int		side;
	double	perpWallDist;

	data->rayDirX = rayDirX;
	data->rayDirY = rayDirY;
	if (rayDirX)
		deltaDistX = fabs(1/ rayDirX);
	else
		deltaDistX = 1e30;
	if (rayDirY)
		deltaDistY = fabs(1/ rayDirY);
	else
		deltaDistY = 1e30;
	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (posX - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (posY - mapY) * deltaDistY;
	}	
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	}

	while (!hit)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (data->map[mapY][mapX] == '1')
			hit = true;
	}
	if (!side)
	{
		perpWallDist = sideDistX - deltaDistX;
		data->wallX = posY + perpWallDist * rayDirY;
	}
	else
	{
		perpWallDist = sideDistY - deltaDistY;
		data->wallX = posX + perpWallDist * rayDirX;

	}
	data->wallX -= floor(data->wallX);
	data->side = side;
	return (perpWallDist);
}

static void	draw_rays(t_data *data)
{
	int		i;
	double	angle;
	double	projplane_halfw;
	double	projplane_x;
	double	x_max;
	double	t;
	double	cx;
	double	cy;

	projplane_halfw = tan(data->fov / 2);
	x_max = WIN_W - 1;
	i = -1;
	while (++i < WIN_W)
	{
		projplane_x = (((i * 2) - x_max) / x_max) * (projplane_halfw);
		angle = data->player_a + atan(projplane_x);
		cx = data->player_x + cos(angle);
		cy = data->player_y + sin(angle);
		t = dda(data, cx, cy);
		draw_vertical_ray(data, i, WIN_H / (t * cos(angle - data->player_a)));
	}
}

static int	render(t_data *data)
{
	if (time_ms() - data->last_frame_time >= 16)
	{
		data->last_frame_time = time_ms();
		player_move(data);
		draw_map(data);
		draw_rays(data);
		draw_player(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
	}
	return (0);
}

int	main(void)
{
	char	*map[] = {"1111111111111111", \
					"1000000000000001", \
					"1000000111110001", \
					"1000001000000001", \
					"1000001001111111", \
					"1000001000000001", \
					"1000111110000001", \
					"1000100011111001", \
					"1000100010000001", \
					"1000100010011111", \
					"1000000010000001", \
					"1000000010000001", \
					"1000000010000001", \
					"1011111110000001", \
					"1000000000000001", \
					"1111111111111111"};
	t_data	data;

	init_data(&data, map);
	events_init(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
