/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:42:11 by mcygan            #+#    #+#             */
/*   Updated: 2025/01/23 15:43:48 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <mlx.h>
#include <stdio.h>
#include <math.h>

#define WIDTH	1024
#define HEIGHT	768

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef t_vec	t_point;
typedef t_vec	t_colour;

typedef struct s_ray
{
	t_point	origin;
	t_vec	dir;
}	t_ray;
