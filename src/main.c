/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:30:03 by mcygan            #+#    #+#             */
/*   Updated: 2025/01/30 15:13:29 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
				draw_tile(&data->img, j, i, 0x0F0F00);
			else
				draw_tile(&data->img, j, i, 0x5F5F5F);
		}
	}
}

static void	draw_vertical_ray(t_img *img, int x, int h)
{
	int	ceiling;
	int	floor;
	int	i;

	ceiling = (WIN_H - h) / 2;
	floor = ceiling + h;
	if (floor > WIN_H)
		floor = WIN_H;
	if (x < MAP_W * MAP_SCALE)
		i = MAP_H * MAP_SCALE;
	else
		i = 0;
	while (i < ceiling)
		pxl_put(img, x, i++, 0x99DDFF);
	while (i < floor)
		pxl_put(img, x, i++, 0x15805F);
	while (i < WIN_H)
		pxl_put(img, x, i++, 0x36220A);
}

static void	draw_rays(t_data *data)
{
	int		i;
	float	angle;
	float	t;
	float	cx;
	float	cy;

	i = -1;
	while (++i < WIN_W)
	{
		angle = data->player_a - data->fov / 2 + data->fov * i / (float)WIN_W;
		t = 0.0;
		while (t < 20.0)
		{
			cx = data->player_x + t * cos(angle);
			cy = data->player_y + t * sin(angle);
			if (data->map[(int)cy][(int)cx] == '1')
				break ;
			pxl_put(&data->img, (int)(cx * MAP_SCALE), (int)(cy * MAP_SCALE), 0xFFFFFF);
			t += 0.01;
		}
		draw_vertical_ray(&data->img, i, WIN_H / (t * cos(angle - data->player_a)));
	}
}

static void	render(t_data *data)
{
	draw_map(data);
	draw_rays(data);
	draw_player(data);
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
	while (1)
	{
		render(&data);
		mlx_put_image_to_window(data.mlx, data.win, data.img.ptr, 0, 0);
		data.player_a += 0.01;
		usleep(5000);
	}
	mlx_loop(data.mlx);
	return (0);
}
