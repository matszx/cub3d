/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:30:03 by mcygan            #+#    #+#             */
/*   Updated: 2025/03/31 13:47:29 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static t_img	init_texture(t_data *data, char *path)
{
	t_img	tex;

	path[ft_strlen(path) - 1] = 0;
	tex.ptr = mlx_xpm_file_to_image(data->mlx, path, &tex.w, &tex.h);
	if (!(tex.ptr))
		close_handler(data, "can't load texture");
	tex.addr = mlx_get_data_addr(tex.ptr, &tex.bpp, &tex.line_len, &tex.endian);
	if (!(tex.addr))
		close_handler(data, "can't get texture memory address");
	return (tex);
}

int	main(int argc, char **argv)
{
	char	*map[] = {"1111111111111111", \
					"1000000000000001", \
					"1000000111110001", \
					"1000001000000001", \
					"1000001001111111", \
					"1000001000000001", \
					"1000111110000001", \
					"1000100011111001", \
					"1000100010000001", \
					"1000100010011111", \
					"1000000010000001", \
					"1000000010000001", \
					"1000000010000001", \
					"1011111110000001", \
					"1000000000000001", \
					"1111111111111111"};
	t_data	data;

	if (argc != 2)
		close_handler(&data, "program takes a single argument");
	init_data(&data, map);
	if (parse_cfg(&data, argv[1]))
		close_handler(&data, "invalid path");
	data.tex_no = init_texture(&data, data.tex_no_path);
	data.tex_so = init_texture(&data, data.tex_so_path);
	data.tex_we = init_texture(&data, data.tex_we_path);
	data.tex_ea = init_texture(&data, data.tex_ea_path);
	init_events(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
