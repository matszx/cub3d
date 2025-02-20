/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:15:05 by mcygan            #+#    #+#             */
/*   Updated: 2025/02/20 16:44:46 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* static int	tex_pxl_colour(t_data *data, int y, int h)
{
	int	texX;
	int	texY;

	texX = data->wallX * data->texture.w;
	if ((data->side && data->rayDirY < 0) || (!data->side && data->rayDirX > 0))
		texX = data->texture.w - texX - 1;
	texY = ((double)y / (double)h) * (double)data->texture.h;
	return (data->texture.addr[data->texture.w * texY + texX]);
} */

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
		pxl_put(&data->img, x, i++, 0x124725);
	while (i < WIN_H)
		pxl_put(&data->img, x, i++, 0x2F1600);
}

static double	dda(t_data *data, double cx, double cy)
{
	double	rayDirX = cx - data->pos_x;
	double	rayDirY = cy - data->pos_y;
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

	if (rayDirX)
		deltaDistX = fabs(1 / rayDirX);
	else
		deltaDistX = INFINITY;
	if (rayDirY)
		deltaDistY = fabs(1 / rayDirY);
	else
		deltaDistY = INFINITY;
	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (data->pos_x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - data->pos_x) * deltaDistX;
	}
	if (rayDirY < 0)
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
		perpWallDist = sideDistX - deltaDistX;
	else
		perpWallDist = sideDistY - deltaDistY;
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
