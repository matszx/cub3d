/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:43:44 by mcygan            #+#    #+#             */
/*   Updated: 2025/01/30 15:37:06 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	close_handler(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.ptr);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_SUCCESS);
}

static int	key_handler(int keycode, t_data *data)
{
	if (keycode == 0x61)
		data->player_x += 0.05;
	else if (keycode == 0x64)
		data->player_x -= 0.05;
	else if (keycode == 0x77)
		data->player_y += 0.05;
	else if (keycode == 0x73)
		data->player_y -= 0.05;
	else if (keycode == 0x65)
		data->player_a += 0.05;
	else if (keycode == 0x71)
		data->player_a -= 0.05;
	if (keycode == 0xff1b)
		close_handler(data);
	render(data);
	return (0);
}

void	events_init(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_handler, data);
}
