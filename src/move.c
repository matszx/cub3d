/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:03:55 by mcygan            #+#    #+#             */
/*   Updated: 2025/02/12 13:38:23 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_W(t_data *data)
{
	data->player_x += cos(data->player_a) * 0.05;
	data->player_y += sin(data->player_a) * 0.05;
}

void	move_A(t_data *data)
{
	data->player_x += cos(data->player_a - M_PI / 2) * 0.05;
	data->player_y += sin(data->player_a - M_PI / 2) * 0.05;
}

void	move_S(t_data *data)
{
	data->player_x -= cos(data->player_a) * 0.05;
	data->player_y -= sin(data->player_a) * 0.05;
}

void	move_D(t_data *data)
{
	data->player_x += cos(data->player_a + M_PI / 2) * 0.05;
	data->player_y += sin(data->player_a + M_PI / 2) * 0.05;
}
