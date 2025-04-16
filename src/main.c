/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:30:03 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/16 11:57:00 by mcygan           ###   ########.fr       */
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

static void	load_textures(t_data *data)
{
	data->tex_no = init_texture(data, data->tex_no_path);
	data->tex_so = init_texture(data, data->tex_so_path);
	data->tex_we = init_texture(data, data->tex_we_path);
	data->tex_ea = init_texture(data, data->tex_ea_path);
}

static int	parse_map(t_data *data)
{
	int	i;
	int	j;

	data->map = get_map(data->fd);
	if (!data->map)
		return (1);
	set_map_size(data);
	data->check = init_check_matrix(data);
	if (!data->check)
		return (1);
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (++j < data->map_w)
		{
			if (!data->check[i][j] && (data->map[i][j] == '0'\
				|| data->map[i][j] == 'N' || data->map[i][j] == 'S'\
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E'))
				parse_cluster(data, j, i);
		}
	}
	if (data->pos_x < 0)
		data->error++;
	return (data->error);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		close_handler(NULL, "needs single argument");
	data.fd = open(argv[1], O_RDONLY);
	if (data.fd < 0)
		close_handler(NULL, "invalid path");
	init_data(&data);
	init_events(&data);
	if (parse_cfg(&data))
		close_handler(&data, "settings misconfigured");
	if (parse_map(&data))
		close_handler(&data, "map misconfigured");
	load_textures(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
