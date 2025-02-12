/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:03:55 by mcygan            #+#    #+#             */
/*   Updated: 2025/02/12 14:20:06 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	valid_pos(t_data *data, float x, float y)
{
	if (x <= 0 || x >= data->map_w || y <= 0 || y >= data->map_h)
		return (0);
	// doesn´t work for some reason
	/* if (data->map[(int)x][(int)y] == 1)
		return (0); */
	return (1);
}

void	move_W(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player_x + cos(data->player_a) * 0.05;
	new_y = data->player_y + sin(data->player_a) * 0.05;
	if (valid_pos(data, new_x, new_y))
	{
		data->player_x = new_x;
		data->player_y = new_y;
	}
}

void	move_A(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player_x + cos(data->player_a - M_PI / 2) * 0.05;
	new_y = data->player_y + sin(data->player_a - M_PI / 2) * 0.05;
	if (valid_pos(data, new_x, new_y))
	{
		data->player_x = new_x;
		data->player_y = new_y;
	}
}

void	move_S(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player_x - cos(data->player_a) * 0.05;
	new_y = data->player_y - sin(data->player_a) * 0.05;
	if (valid_pos(data, new_x, new_y))
	{
		data->player_x = new_x;
		data->player_y = new_y;
	}
}

void	move_D(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player_x + cos(data->player_a + M_PI / 2) * 0.05;
	new_y = data->player_y + sin(data->player_a + M_PI / 2) * 0.05;
	if (valid_pos(data, new_x, new_y))
	{
		data->player_x = new_x;
		data->player_y = new_y;
	}
}
