/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:15:05 by mcygan            #+#    #+#             */
/*   Updated: 2025/03/13 16:54:05 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	draw_vertical_ray(t_data *data, int x, int h, double perp_dist)
{
	int	ceiling;
	int	floor;
	int	i;

	ceiling = (WIN_H - h) / 2;
	floor = ceiling + h;
	if (floor > WIN_H)
		floor = WIN_H;
	if (x < MAP_W * MAP_SCALE)
		i = MAP_H * MAP_SCALE;
	else
		i = 0;
	while (i < ceiling)
		pxl_put(&data->img, x, i++, 0x99DDFF);
	while (i < floor)
	{
		pxl_put(&data->img, x, i, get_texel(data, i - ceiling, h, perp_dist));
		i++;
	}
	while (i < WIN_H)
		pxl_put(&data->img, x, i++, 0x2F1600);
}

static double	dda(t_data *data, double cx, double cy)
{
	double	deltaDistX;
	double	deltaDistY;
	int		mapX = (int)data->pos_x;
	int		mapY = (int)data->pos_y;
	double	sideDistX;
	double	sideDistY;
	int		stepX;
	int		stepY;

	data->raydir_x = cx - data->pos_x;
	data->raydir_y = cy - data->pos_y;
	if (data->raydir_x)
		deltaDistX = fabs(1 / data->raydir_x);
	else
		deltaDistX = INFINITY;
	if (data->raydir_y)
		deltaDistY = fabs(1 / data->raydir_y);
	else
		deltaDistY = INFINITY;
	if (data->raydir_x < 0)
	{
		stepX = -1;
		sideDistX = (data->pos_x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - data->pos_x) * deltaDistX;
	}
	if (data->raydir_y < 0)
	{
		stepY = -1;
		sideDistY = (data->pos_y - mapY) * deltaDistY;
	}	
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - data->pos_y) * deltaDistY;
	}
	while (1)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			data->side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			data->side = 1;
		}
		if (data->map[mapY][mapX] == '1')
			break ;
	}
	if (!data->side)
		return (sideDistX - deltaDistX);
	else
		return (sideDistY - deltaDistY);
}

static void	cast_rays(t_data *data)
{
	int		i;
	double	projplane_x;
	double	angle;
	double	t;

	i = -1;
	while (++i < WIN_W)
	{
		projplane_x = (i * 2.0 - WIN_W) / WIN_W * tan(data->fov / 2);
		angle = data->pos_a + atan(projplane_x);
		t = dda(data, data->pos_x + cos(angle), data->pos_y + sin(angle));
		data->angle = fmod(angle, M_PI * 2);
		if (data->angle < 0.0)
			data->angle += 2 * M_PI;
		draw_vertical_ray(data, i, WIN_H / (t * cos(angle - data->pos_a)), t);
	}
}

int	render(t_data *data)
{
	if (time_ms() - data->last_frame_time >= 16)
	{
		data->last_frame_time = time_ms();
		player_move(data);
		draw_minimap(data);
		cast_rays(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
	}
	return (0);
}
