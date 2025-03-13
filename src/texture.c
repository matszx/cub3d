/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:55:26 by mcygan            #+#    #+#             */
/*   Updated: 2025/03/13 16:55:13 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static t_img	*get_texture(t_data *data)
{
	const double	half_pi = M_PI / 2;
	const double	threehalves_pi = 3 * M_PI / 2;
	const double	two_pi = 2 * M_PI;

	if (data->angle >= 0 && data->angle < half_pi && data->side)
		return (&data->texture_s);
	if (data->angle >= 0 && data->angle < half_pi && !data->side)
		return (&data->texture_e);
	if (data->angle >= half_pi && data->angle < M_PI && data->side)
		return (&data->texture_s);
	if (data->angle >= half_pi && data->angle < M_PI && !data->side)
		return (&data->texture_w);
	if (data->angle >= M_PI && data->angle < threehalves_pi && data->side)
		return (&data->texture_n);
	if (data->angle >= M_PI && data->angle < threehalves_pi && !data->side)
		return (&data->texture_w);
	if (data->angle >= threehalves_pi && data->angle < two_pi && data->side)
		return (&data->texture_n);
	if (data->angle >= threehalves_pi && data->angle < two_pi && !data->side)
		return (&data->texture_e);
	return (NULL);
}

int	get_texel(t_data *data, int y, int h, double perp_dist)
{
	t_img	*tex;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	char	*dst;

	tex = get_texture(data);
	if (!data->side)
		wall_x = data->pos_y + perp_dist * data->raydir_y;
	else
		wall_x = data->pos_x + perp_dist * data->raydir_x;
	wall_x -= floor(wall_x);
	tex_x = wall_x * tex->w;
	if ((data->side && data->raydir_y > 0.0) || 
		(!data->side && data->raydir_x < 0.0))
		tex_x = tex->w - tex_x - 1;
	tex_y = ((double)y / (double)h) * (double)tex->h;
	dst = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(unsigned int *) dst);
}
