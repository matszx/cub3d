/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:15:05 by mcygan            #+#    #+#             */
/*   Updated: 2025/02/20 14:17:34 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	tex_pxl_colour(t_data *data, int y, int h)
{
	int	texX;
	int	texY;

	texX = data->wallX * data->texture.w;
	if ((data->side && data->rayDirY < 0) || (!data->side && data->rayDirX > 0))
		texX = data->texture.w - texX - 1;
	texY = ((double)y / (double)h) * (double)data->texture.h;
	return (data->texture.addr[data->texture.w * texY + texX]);
}

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
		i = MAP_H * MAP_SCALE - 1;
	else
		i = -1;
	while (++i < ceiling)
		pxl_put(&data->img, x, i, 0x99DDFF);
	while (++i < floor)
		pxl_put(&data->img, x, i, tex_pxl_colour(data, i - ceiling, h));
	while (++i < WIN_H)
		pxl_put(&data->img, x, i, 0x2F1600);
}

static double	dda(t_data *data, double cx, double cy)
{
	double	posX = data->player_x;
	double	posY = data->player_y;
	double	rayDirX = cx - posX;
	double	rayDirY = cy - posY;
	double	deltaDistX;
	double	deltaDistY;
	int		mapX = (int)posX;
	int		mapY = (int)posY;
	double	sideDistX;
	double	sideDistY;
	int		stepX;
	int		stepY;
	bool	hit = false;
	int		side;
	double	perpWallDist;

	data->rayDirX = rayDirX;
	data->rayDirY = rayDirY;
	if (rayDirX)
		deltaDistX = fabs(1/ rayDirX);
	else
		deltaDistX = 1e30;
	if (rayDirY)
		deltaDistY = fabs(1/ rayDirY);
	else
		deltaDistY = 1e30;
	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (posX - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (posY - mapY) * deltaDistY;
	}	
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
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
		data->wallX = posY + perpWallDist * rayDirY;
	}
	else
	{
		perpWallDist = sideDistY - deltaDistY;
		data->wallX = posX + perpWallDist * rayDirX;

	}
	data->wallX -= floor(data->wallX);
	data->side = side;
	return (perpWallDist);
}

static void	draw_rays(t_data *data)
{
	int		i;
	double	angle;
	double	projplane_halfw;
	double	projplane_x;
	double	x_max;
	double	t;
	double	cx;
	double	cy;

	projplane_halfw = tan(data->fov / 2);
	x_max = WIN_W - 1;
	i = -1;
	while (++i < WIN_W)
	{
		projplane_x = (((i * 2) - x_max) / x_max) * (projplane_halfw);
		angle = data->player_a + atan(projplane_x);
		cx = data->player_x + cos(angle);
		cy = data->player_y + sin(angle);
		t = dda(data, cx, cy);
		draw_vertical_ray(data, i, WIN_H / (t * cos(angle - data->player_a)));
	}
}

int	render(t_data *data)
{
	if (time_ms() - data->last_frame_time >= 16)
	{
		data->last_frame_time = time_ms();
		player_move(data);
		draw_minimap(data);
		draw_rays(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
	}
	return (0);
}
