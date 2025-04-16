/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:04:10 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/16 11:06:36 by mcygan           ###   ########.fr       */
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

char	**init_check_matrix(t_data *data)
{
	char	**check_matrix;
	int		i;
	int		j;

	check_matrix = malloc(sizeof(char *) * (data->map_h + 1));
	if (!check_matrix)
		return (NULL);
	i = -1;
	while (++i < data->map_h)
	{
		check_matrix[i] = malloc(sizeof(char) * (data->map_w + 1));
		if (!check_matrix[i])
		{
			while (i--)
				free(check_matrix[i]);
			return (free(check_matrix), NULL);
		}
		j = -1;
		while (++j < data->map_w)
			check_matrix[i][j] = 0;
		check_matrix[i][j] = '\n';
	}
	check_matrix[i] = NULL;
	return (check_matrix);
}

void	init_data(t_data *data)
{
	init_mlx(data);
	data->error = 0;
	data->pos_x = -1;
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
