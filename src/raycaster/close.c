/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:56:00 by mcygan            #+#    #+#             */
/*   Updated: 2025/05/28 00:48:22 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	destroy_image(void *mlx, void *img)
{
	if (!mlx || !img)
		return ;
	mlx_destroy_image(mlx, img);
}

static void	destroy_images(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 5)
		destroy_image(data->mlx, data->sprite[i].ptr);
	destroy_image(data->mlx, data->tex_no.ptr);
	destroy_image(data->mlx, data->tex_so.ptr);
	destroy_image(data->mlx, data->tex_we.ptr);
	destroy_image(data->mlx, data->tex_ea.ptr);
	destroy_image(data->mlx, data->img.ptr);
}

static void	finish_reading(int fd)
{
	char *line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	close_handler(t_data *data, char *error)
{
	if (data)
	{
		finish_reading(data->fd);
		if (data->mlx)
		{
			free_cfg(data->cfg);
			free_str_array(data->map);
			destroy_images(data);
			if (data->win)
				mlx_destroy_window(data->mlx, data->win);
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
	}
	if (error)
		printf("\x1b[1;31mError:\x1b[0m %s\n", error);
	exit(error != NULL);
}
