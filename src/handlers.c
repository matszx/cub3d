/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:43:44 by mcygan            #+#    #+#             */
/*   Updated: 2025/02/12 18:49:42 by mcygan           ###   ########.fr       */
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

static int	key_press_handler(int keycode, t_data *data)
{
	if (keycode == 0x77)
		data->w_press = true;
	else if (keycode == 0x61)
		data->a_press = true;
	else if (keycode == 0x73)
		data->s_press = true;
	else if (keycode == 0x64)
		data->d_press = true;
	else if (keycode == 0xff51)
		data->left_press = true;
	else if (keycode == 0xff53)
		data->right_press = true;
	else if (keycode == 0xff1b)
		close_handler(data);
	return (0);
}

static int	key_release_handler(int keycode, t_data *data)
{
	if (keycode == 0x77 && data->w_press)
		data->w_press = false;
	else if (keycode == 0x61 && data->a_press)
		data->a_press = false;
	else if (keycode == 0x73 && data->s_press)
		data->s_press = false;
	else if (keycode == 0x64 && data->d_press)
		data->d_press = false;
	else if (keycode == 0xff51 && data->left_press)
		data->left_press = false;
	else if (keycode == 0xff53 && data->right_press)
		data->right_press = false;
	return (0);
}

void	events_init(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_press_handler, data);
	mlx_hook(data->win, 3, 1L << 1, key_release_handler, data);
}
