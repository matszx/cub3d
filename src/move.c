/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:03:55 by mcygan            #+#    #+#             */
/*   Updated: 2025/02/20 16:23:47 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	move_w(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x + cos(data->pos_a) * MOVE_SPEED;
	new_y = data->pos_y + sin(data->pos_a) * MOVE_SPEED;
	if (data->map[(int)data->pos_y][(int)new_x] != '1')
		data->pos_x = new_x;
	if (data->map[(int)new_y][(int)data->pos_x] != '1')
		data->pos_y = new_y;
}

static void	move_a(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x + cos(data->pos_a - M_PI / 2) * MOVE_SPEED;
	new_y = data->pos_y + sin(data->pos_a - M_PI / 2) * MOVE_SPEED;
	if (data->map[(int)data->pos_y][(int)new_x] != '1')
		data->pos_x = new_x;
	if (data->map[(int)new_y][(int)data->pos_x] != '1')
		data->pos_y = new_y;
}

static void	move_s(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x - cos(data->pos_a) * MOVE_SPEED;
	new_y = data->pos_y - sin(data->pos_a) * MOVE_SPEED;
	if (data->map[(int)data->pos_y][(int)new_x] != '1')
		data->pos_x = new_x;
	if (data->map[(int)new_y][(int)data->pos_x] != '1')
		data->pos_y = new_y;
}

static void	move_d(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x + cos(data->pos_a + M_PI / 2) * MOVE_SPEED;
	new_y = data->pos_y + sin(data->pos_a + M_PI / 2) * MOVE_SPEED;
	if (data->map[(int)data->pos_y][(int)new_x] != '1')
		data->pos_x = new_x;
	if (data->map[(int)new_y][(int)data->pos_x] != '1')
		data->pos_y = new_y;
}

void	player_move(t_data *data)
{
	if (data->w_press)
		move_w(data);
	if (data->a_press)
		move_a(data);
	if (data->s_press)
		move_s(data);
	if (data->d_press)
		move_d(data);
	if (data->left_press)
		data->pos_a -= MOVE_SPEED;
	if (data->right_press)
		data->pos_a += MOVE_SPEED;
}
