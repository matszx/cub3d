/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:30:03 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/27 23:26:54 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	size_t	pathlen;

	if (argc != 2)
		close_handler(NULL, "needs single argument");
	data.fd = open(argv[1], O_RDONLY);
	if (data.fd < 0)
		close_handler(NULL, "invalid path");
	pathlen = ft_strlen(argv[1]);
	if (pathlen < 5 || ft_strcmp(argv[1] + pathlen - 4, ".cub"))
	{
		close(data.fd);
		close_handler(NULL, "wrong filetype");
	}
	init_data(&data);
	init_events(&data);
	parse(&data);
	load_textures(&data);
	load_sprites(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
