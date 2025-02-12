/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:03:55 by mcygan            #+#    #+#             */
/*   Updated: 2025/02/12 15:42:28 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_w(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player_x + cos(data->player_a) * MOVE_SPEED;
	new_y = data->player_y + sin(data->player_a) * MOVE_SPEED;
	if (data->map[(int)data->player_y][(int)new_x] != '1')
		data->player_x = new_x;
	if (data->map[(int)new_y][(int)data->player_x] != '1')
		data->player_y = new_y;
}

void	move_a(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player_x + cos(data->player_a - M_PI / 2) * MOVE_SPEED;
	new_y = data->player_y + sin(data->player_a - M_PI / 2) * MOVE_SPEED;
	if (data->map[(int)data->player_y][(int)new_x] != '1')
		data->player_x = new_x;
	if (data->map[(int)new_y][(int)data->player_x] != '1')
		data->player_y = new_y;
}

void	move_s(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player_x - cos(data->player_a) * MOVE_SPEED;
	new_y = data->player_y - sin(data->player_a) * MOVE_SPEED;
	if (data->map[(int)data->player_y][(int)new_x] != '1')
		data->player_x = new_x;
	if (data->map[(int)new_y][(int)data->player_x] != '1')
		data->player_y = new_y;
}

void	move_d(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player_x + cos(data->player_a + M_PI / 2) * MOVE_SPEED;
	new_y = data->player_y + sin(data->player_a + M_PI / 2) * MOVE_SPEED;
	if (data->map[(int)data->player_y][(int)new_x] != '1')
		data->player_x = new_x;
	if (data->map[(int)new_y][(int)data->player_x] != '1')
		data->player_y = new_y;
}
