/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:30:03 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/10 00:00:23 by mcygan           ###   ########.fr       */
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

static int	parse_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (++j < data->grid_w)
		{
			if (!data->check[i][j] && (data->map[i][j] == '0'\
				|| data->map[i][j] == 'N' || data->map[i][j] == 'S'\
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E'))
				parse_cluster(data, j, i);
		}
	}
	return (data->error);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		close_handler(NULL, "needs single argument");
	init_data(&data);
	if (parse_cfg(&data, argv[1]))
		close_handler(&data, "invalid path");
	data.map = get_map(data.fd);
	if (!data.map)
		close_handler(&data, "can't load map");
	set_map_size(&data);
	data.check = init_check_matrix(&data);
	if (parse_map(&data))
		close_handler(&data, "map misconfigured");
	data.tex_no = init_texture(&data, data.tex_no_path);
	data.tex_so = init_texture(&data, data.tex_so_path);
	data.tex_we = init_texture(&data, data.tex_we_path);
	data.tex_ea = init_texture(&data, data.tex_ea_path);
	init_events(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
