/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:30:03 by mcygan            #+#    #+#             */
/*   Updated: 2025/01/23 18:53:44 by mcygan           ###   ########.fr       */
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
				draw_tile(img, j, i, 0x000F0F00);
			else
				draw_tile(img, j, i, 0x5F5F5F5F);
		}
	}
}

int	main(void)
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
	void		*mlx;
	void		*win;
	t_img		img;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "cub3d");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	draw_map(&img, map, 16, 16);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
