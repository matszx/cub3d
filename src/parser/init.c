/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:04:10 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/27 18:17:20 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, "cub3d");
	if (!data->win)
		return (1);
	data->img.ptr = mlx_new_image(data->mlx, WIN_W, WIN_H);
	if (!data->img.ptr)
		return (1);
	data->img.addr = mlx_get_data_addr(\
		data->img.ptr, &data->img.bpp, &data->img.line_len, &data->img.endian);
	if (!data->img.addr)
		return (1);
	return (0);
}

void	init_data(t_data *data)
{
	if (init_mlx(data))
		close_handler(data, "can't load mlx");
	data->error = 0;
	data->tex_no_path = NULL;
	data->tex_so_path = NULL;
	data->tex_we_path = NULL;
	data->tex_ea_path = NULL;
	data->floor_colour = -1;
	data->ceiling_colour = -1;
	data->pos_x = -1;
	data->fov = M_PI / (180.0 / FOV);
	data->w_press = false;
	data->a_press = false;
	data->s_press = false;
	data->d_press = false;
	data->left_press = false;
	data->right_press = false;
	data->mouse_lastpos = WIN_W / 2;
	data->mouse_move = 0;
	data->animation = false;
	data->frame = 0;
	data->last_sprite_time = time_ms();
	data->last_frame_time = time_ms();
}

int	init_img(t_data *data, char *path, t_img *addr)
{
	t_img	img;
	size_t	pathlen;

	pathlen = ft_strlen(path);
	if (path[pathlen - 1] == '\n')
		path[pathlen - 1] = 0;
	img.ptr = mlx_xpm_file_to_image(data->mlx, path, &img.w, &img.h);
	if (!(img.ptr))
		return (1);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.line_len, &img.endian);
	if (!(img.addr))
		return (1);
	*addr = img;
	return (0);
}

void	load_textures(t_data *data)
{
	if (init_img(data, data->tex_no_path, &data->tex_no) || \
		init_img(data, data->tex_so_path, &data->tex_so) || \
		init_img(data, data->tex_we_path, &data->tex_we) || \
		init_img(data, data->tex_ea_path, &data->tex_ea))
		close_handler(data, "can't load texture");
}
