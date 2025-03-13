/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:55:26 by mcygan            #+#    #+#             */
/*   Updated: 2025/03/13 22:33:52 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static t_img	*get_texture(t_data *data, t_ray_info *info)
{
	const double	half_pi = M_PI / 2;
	const double	threehalves_pi = 3 * M_PI / 2;
	const double	two_pi = 2 * M_PI;

	if (info->angle >= 0 && info->angle < half_pi && info->side)
		return (&data->texture_s);
	if (info->angle >= 0 && info->angle < half_pi && !info->side)
		return (&data->texture_e);
	if (info->angle >= half_pi && info->angle < M_PI && info->side)
		return (&data->texture_s);
	if (info->angle >= half_pi && info->angle < M_PI && !info->side)
		return (&data->texture_w);
	if (info->angle >= M_PI && info->angle < threehalves_pi && info->side)
		return (&data->texture_n);
	if (info->angle >= M_PI && info->angle < threehalves_pi && !info->side)
		return (&data->texture_w);
	if (info->angle >= threehalves_pi && info->angle < two_pi && info->side)
		return (&data->texture_n);
	if (info->angle >= threehalves_pi && info->angle < two_pi && !info->side)
		return (&data->texture_e);
	return (NULL);
}

int	get_texel(t_data *data, t_ray_info *info, int y, int wall_h)
{
	t_img	*tex;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	char	*dst;

	tex = get_texture(data, info);
	if (!info->side)
		wall_x = data->pos_y + info->perp_dist * info->raydir_y;
	else
		wall_x = data->pos_x + info->perp_dist * info->raydir_x;
	wall_x -= floor(wall_x);
	tex_x = wall_x * tex->w;
	if ((info->side && info->raydir_y > 0.0) || \
		(!info->side && info->raydir_x < 0.0))
		tex_x = tex->w - tex_x - 1;
	tex_y = ((double)y / wall_h) * tex->h;
	dst = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(unsigned int *) dst);
}
