/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:58:17 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/17 13:17:22 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	load_sprites(t_data *data)
{
	if (init_img(data, "./sprites/gun1.xpm", &data->sprite))/*  || \
		init_img(data, "./sprites/gun2.xpm", &data->sprite) || \
		init_img(data, "./sprites/gun3.xpm", &data->sprite) || \
		init_img(data, "./sprites/gun4.xpm", &data->sprite) || \
		init_img(data, "./sprites/gun5.xpm", &data->sprite)) */
		close_handler(data, "can't load sprite");
}

void	put_sprite_to_img(t_img *img, t_img *sprite, int x, int y)
{
	int	i;
	int	j;
	int	colour;

	i = -1;
	while(++i < sprite->w)
	{
		j = -1;
		while (++j < sprite->h)
		{
			colour = get_pxl(sprite, i, j);
			if (colour != (int)0xFF000000)
				pxl_put(img, x + i, y + j, colour);
		}
	}
}
