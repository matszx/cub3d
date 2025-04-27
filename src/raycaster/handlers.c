/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:43:44 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/27 17:59:56 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	close_handler(t_data *data, char *error)
{
	int	i;

	if (!data)
		return (printf("\x1b[1;31mError:\x1b[0m %s\n", error), exit(1));
	close(data->fd);
	if (data->mlx)
	{
		free_cfg(data->cfg);
		if (data->img.ptr)
			mlx_destroy_image(data->mlx, data->img.ptr);
		i = -1;
		while (++i < 5)
		{
			if (data->sprite[i].ptr)
				mlx_destroy_image(data->mlx, data->sprite[i].ptr);
		}
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (!error)
		return (exit(0));
	return (printf("\x1b[1;31mError:\x1b[0m %s\n", error), exit(1));
}

static int	key_press_handler(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->w_press = true;
	else if (keycode == KEY_A)
		data->a_press = true;
	else if (keycode == KEY_S)
		data->s_press = true;
	else if (keycode == KEY_D)
		data->d_press = true;
	else if (keycode == KEY_LEFT)
		data->left_press = true;
	else if (keycode == KEY_RIGHT)
		data->right_press = true;
	else if (keycode == KEY_SPACE)
		data->animation = true;
	else if (keycode == KEY_ESCAPE)
		close_handler(data, NULL);
	return (0);
}

static int	key_release_handler(int keycode, t_data *data)
{
	if (keycode == KEY_W && data->w_press)
		data->w_press = false;
	else if (keycode == KEY_A && data->a_press)
		data->a_press = false;
	else if (keycode == KEY_S && data->s_press)
		data->s_press = false;
	else if (keycode == KEY_D && data->d_press)
		data->d_press = false;
	else if (keycode == KEY_LEFT && data->left_press)
		data->left_press = false;
	else if (keycode == KEY_RIGHT && data->right_press)
		data->right_press = false;
	return (0);
}

static int	mouse_handler(int x, int y, t_data *data)
{
	(void)y;
	data->mouse_move += x - data->mouse_lastpos;
	data->mouse_lastpos = x;
	return (0);
}

void	init_events(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_press_handler, data);
	mlx_hook(data->win, 3, 1L << 1, key_release_handler, data);
	if (MOUSE)
		mlx_hook(data->win, 6, 1L << 6, mouse_handler, data);
}
