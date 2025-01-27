/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:30:03 by mcygan            #+#    #+#             */
/*   Updated: 2025/01/27 15:17:07 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <unistd.h>

static void	draw_map(t_img *img, const char **map, uint32_t w, uint32_t h)
{
	uint32_t	i;
	uint32_t	j;

	i = -1;
	while (++i < h)
	{
		j = -1;
		while (++j < w)
		{
			if (map[i][j] == '1')
				draw_tile(img, j, i, 0x0F0F00);
			else
				draw_tile(img, j, i, 0x5F5F5F);
		}
	}
}

static void	draw_vertical_ray(t_img *img, uint32_t x, uint32_t h)
{
	const uint32_t	ceiling = (WIN_H - h) / 2;
	const uint32_t	floor = ceiling + h;
	uint32_t		i;

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

static void	draw_rays(t_img *img, const char **map, float px, float py, float pa)
{
	const float	fov = M_PI / (180 / FOV);
	uint32_t	i;
	float		angle;
	float		t;
	float		cx;
	float		cy;

	i = -1;
	while (++i < WIN_W)
	{
		angle = pa - fov / 2 + fov * i / (float)WIN_W;
		t = 0.0;
		while (t < 20.0)
		{
			cx = px + t * cos(angle);
			cy = py + t * sin(angle);
			if (map[(int)cy][(int)cx] == '1')
				break ;
			pxl_put(img, (uint32_t)(cx * MAP_SCALE), (uint32_t)(cy * MAP_SCALE), 0xFFFFFF);
			t += 0.01;
		}
		draw_vertical_ray(img, i, WIN_H / t);
	}
}

static void	render(t_img *img, float angle)
{
	const char	*map[] = {"1111111111111111", \
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
	float		player_x = 3.4;
	float		player_y = 2.3;

	draw_map(img, map, MAP_W, MAP_H);
	draw_rays(img, map, player_x, player_y, angle);
	draw_player(img, player_x, player_y);
}

int	main(void)
{
	void		*mlx;
	void		*win;
	t_img		img;
	float		angle;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIN_W, WIN_H, "cub3d");
	img.img = mlx_new_image(mlx, WIN_W, WIN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	angle = 1.5;
	while (1)
	{
		render(&img, angle);
		mlx_put_image_to_window(mlx, win, img.img, 0, 0);
		angle += 0.01;
		usleep(33000);
	}
	mlx_loop(mlx);
	return (0);
}
