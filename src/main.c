/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:30:03 by mcygan            #+#    #+#             */
/*   Updated: 2025/01/27 00:19:25 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

static void	draw_rays(t_img *img, const char **map, float px, float py, float pa)
{
	const float	fov = M_PI / (180 / FOV);
	uint32_t	i;
	float		angle;
	float		t;
	float		cx;
	float		cy;

	i = -1;
	while (++i < WIDTH)
	{
		angle = pa - fov / 2 + fov * i / (float)WIDTH;
		t = 0.0;
		while (t < 20.0)
		{
			cx = px + t * cos(angle);
			cy = py + t * sin(angle);
			if (map[(int)cy][(int)cx] == '1')
				break ;
			pxl_put(img, (uint32_t)(cx * TILE_SIZE), (uint32_t)(cy * TILE_SIZE), 0xFFFFFF);
			t += 0.05;
		}
	}
}

int	main(void)
{
	void		*mlx;
	void		*win;
	t_img		img;

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

	float		player_x = 3.456;
	float		player_y = 2.345;
	float		player_a = 1.523;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "cub3d");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	
	draw_map(&img, map, 16, 16);
	draw_player(&img, player_x, player_y);
	draw_rays(&img, map, player_x, player_y, player_a);

	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	
	return (0);
}
