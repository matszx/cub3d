/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:04:10 by mcygan            #+#    #+#             */
/*   Updated: 2025/03/14 00:27:51 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static t_img	init_texture(t_data *data, char *path)
{
	t_img	tex;

	tex.ptr = mlx_xpm_file_to_image(data->mlx, path, &tex.w, &tex.h);
	if (!(tex.ptr))
		close_handler(data, "can't load texture");
	tex.addr = mlx_get_data_addr(tex.ptr, &tex.bpp, &tex.line_len, &tex.endian);
	if (!(tex.addr))
		close_handler(data, "can't get texture memory address");
	return (tex);
}

static void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		close_handler(data, "can't initialise minilibx");
	data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, "cub3d");
	if (!data->win)
		close_handler(data, "can't initialise window");
	data->img.ptr = mlx_new_image(data->mlx, WIN_W, WIN_H);
	if (!data->img.ptr)
		close_handler(data, "can't initialise image");
	data->img.addr = mlx_get_data_addr(\
		data->img.ptr, &data->img.bpp, &data->img.line_len, &data->img.endian);
	if (!data->img.addr)
		close_handler(data, "can't get image memory address");
}

void	init_data(t_data *data, char **map)
{
	init_mlx(data);
	data->map = map;
	data->map_w = 16;
	data->map_h = 16;
	data->pos_x = 1.9;
	data->pos_y = 1.9;
	data->pos_a = 1.5;
	data->fov = M_PI / (180.0 / FOV);
	data->w_press = false;
	data->a_press = false;
	data->s_press = false;
	data->d_press = false;
	data->left_press = false;
	data->right_press = false;
	data->last_frame_time = time_ms();
	data->texture_n = init_texture(data, "./textures/metal.xpm");
	data->texture_e = init_texture(data, "./textures/caca.xpm");
	data->texture_s = init_texture(data, "./textures/brick.xpm");
	data->texture_w = init_texture(data, "./textures/blue.xpm");
}
