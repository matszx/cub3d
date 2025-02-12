/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:43:44 by mcygan            #+#    #+#             */
/*   Updated: 2025/02/12 15:29:32 by mcygan           ###   ########.fr       */
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
	if (keycode == 0x77)
		move_W(data);
	if (keycode == 0x61)
		move_A(data);
	if (keycode == 0x73)
		move_S(data);
	if (keycode == 0x64)
		move_D(data);
	if (keycode == 0xff53)
		data->player_a += MOVE_SPEED / 2;
	if (keycode == 0xff51)
		data->player_a -= MOVE_SPEED / 2;
	if (keycode == 0xff1b)
		close_handler(data);
	return (0);
}

void	events_init(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_handler, data);
}
