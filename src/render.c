/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:15:05 by mcygan            #+#    #+#             */
/*   Updated: 2025/03/13 11:06:51 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	draw_vertical_ray(t_data *data, int x, int h)
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
		pxl_put(&data->img, x, i, get_texel(data, i - ceiling, h));
		i++;
	}
	while (i < WIN_H)
		pxl_put(&data->img, x, i++, 0x2F1600);
}

static double	dda(t_data *data, double cx, double cy)
{
	double	raydir_x = cx - data->pos_x;
	double	raydir_y = cy - data->pos_y;
	double	deltaDistX;
	double	deltaDistY;
	int		mapX = (int)data->pos_x;
	int		mapY = (int)data->pos_y;
	double	sideDistX;
	double	sideDistY;
	int		stepX;
	int		stepY;
	bool	hit = false;
	int		side;
	double	perpWallDist;

	data->raydir_x = raydir_x;
	data->raydir_y = raydir_y;
	if (raydir_x)
		deltaDistX = fabs(1 / raydir_x);
	else
		deltaDistX = INFINITY;
	if (raydir_y)
		deltaDistY = fabs(1 / raydir_y);
	else
		deltaDistY = INFINITY;
	if (raydir_x < 0)
	{
		stepX = -1;
		sideDistX = (data->pos_x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - data->pos_x) * deltaDistX;
	}
	if (raydir_y < 0)
	{
		stepY = -1;
		sideDistY = (data->pos_y - mapY) * deltaDistY;
	}	
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - data->pos_y) * deltaDistY;
	}
	while (!hit)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (data->map[mapY][mapX] == '1')
			hit = true;
	}
	if (!side)
	{
		perpWallDist = sideDistX - deltaDistX;
		data->wall_x = data->pos_y + perpWallDist * raydir_y;
	}
	else
	{
		perpWallDist = sideDistY - deltaDistY;
		data->wall_x = data->pos_x + perpWallDist * raydir_x;
	}
	data->wall_x -= floor(data->wall_x);
	data->tex_x = data->wall_x * 512.0;
	if (side && raydir_y > 0.0)
		data->tex_x = 512 - data->tex_x - 1;
	else if (!side && raydir_x < 0.0)
		data->tex_x = 512 - data->tex_x - 1;
	data->side = side;
	return (perpWallDist);
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
		draw_vertical_ray(data, i, WIN_H / (t * cos(angle - data->pos_a)));
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
