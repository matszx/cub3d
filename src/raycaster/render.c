/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:15:05 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/17 14:50:28 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	draw_vertical_ray(t_data *data, t_ray_info *info, int x)
{
	int	wall_h;
	int	ceiling;
	int	floor;
	int	i;

	wall_h = WIN_H / (info->perp_dist * cos(info->angle - data->pos_a));
	ceiling = (WIN_H - wall_h) / 2;
	floor = ceiling + wall_h;
	if (floor > WIN_H)
		floor = WIN_H;
	if (x < data->map_w * MAP_SCALE)
		i = data->map_h * MAP_SCALE;
	else
		i = 0;
	while (i < ceiling)
		pxl_put(&data->img, x, i++, data->ceiling_colour);
	while (i < floor)
	{
		pxl_put(&data->img, x, i, get_texel(data, info, i - ceiling, wall_h));
		i++;
	}
	while (i < WIN_H)
		pxl_put(&data->img, x, i++, data->floor_colour);
}

static t_ray_info	get_ray_info(t_data *data, double cx, double cy)
{
	t_ray_info	info;

	info.raydir_x = cx - data->pos_x;
	info.raydir_y = cy - data->pos_y;
	info.delta_x = fabs(1 / info.raydir_x);
	info.delta_y = fabs(1 / info.raydir_y);
	info.step_x = 2 * (info.raydir_x > 0) - 1;
	if (info.raydir_x < 0)
		info.side_x = (data->pos_x - (int)data->pos_x) * info.delta_x;
	else
		info.side_x = ((int)data->pos_x + 1.0 - data->pos_x) * info.delta_x;
	info.step_y = 2 * (info.raydir_y > 0) - 1;
	if (info.raydir_y < 0)
		info.side_y = (data->pos_y - (int)data->pos_y) * info.delta_y;
	else
		info.side_y = ((int)data->pos_y + 1.0 - data->pos_y) * info.delta_y;
	return (info);
}

static double	dda(t_data *data, t_ray_info *info)
{
	int			map_x;
	int			map_y;

	map_x = (int)data->pos_x;
	map_y = (int)data->pos_y;
	while (1)
	{
		if (info->side_x < info->side_y)
		{
			info->side_x += info->delta_x;
			map_x += info->step_x;
			info->side = 0;
		}
		else
		{
			info->side_y += info->delta_y;
			map_y += info->step_y;
			info->side = 1;
		}
		if (data->map[map_y][map_x] == '1')
			break ;
	}
	if (!info->side)
		return (info->side_x - info->delta_x);
	return (info->side_y - info->delta_y);
}

static void	cast_rays(t_data *data)
{
	int			i;
	double		projplane_x;
	double		angle;
	t_ray_info	info;

	i = -1;
	while (++i < WIN_W)
	{
		projplane_x = (i * 2.0 - WIN_W) / WIN_W * tan(data->fov / 2);
		angle = data->pos_a + atan(projplane_x);
		info = get_ray_info(\
			data, data->pos_x + cos(angle), data->pos_y + sin(angle));
		info.perp_dist = dda(data, &info);
		info.angle = fmod(angle, M_PI * 2);
		if (info.angle < 0.0)
			info.angle += 2 * M_PI;
		draw_vertical_ray(data, &info, i);
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
		if (data->animation)
			animate_sprite(data);
		put_sprite_to_img(&data->img, &data->sprite[data->frame], \
			5 * WIN_W / 9, WIN_H - data->sprite[data->frame].h - 1);
		mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
	}
	return (0);
}
