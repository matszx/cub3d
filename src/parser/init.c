/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:04:10 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/08 16:17:32 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

void	init_data(t_data *data)
{
	init_mlx(data);
	data->grid_w = 16;
	data->grid_h = 16;
	data->error = 0;
	data->pos_x = -1;
	data->pos_a = -1.5;
	data->fov = M_PI / (180.0 / FOV);
	data->w_press = false;
	data->a_press = false;
	data->s_press = false;
	data->d_press = false;
	data->left_press = false;
	data->right_press = false;
	data->last_frame_time = time_ms();
	data->tex_no_path = NULL;
	data->tex_so_path = NULL;
	data->tex_we_path = NULL;
	data->tex_ea_path = NULL;
	data->floor_colour = -1;
	data->ceiling_colour = -1;
}
