/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:30:03 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/08 16:15:31 by mcygan           ###   ########.fr       */
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
			if (data->map[i][j] == '0'\
				|| data->map[i][j] == 'N' || data->map[i][j] == 'S'\
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				if (!data->check[i][j])
				{
					printf("parse_cluster call at x: %d y: %d\n", j, i);
					parse_cluster(data, j, i);
				}
			}
			/* else if (data->map[i][j] != '1' && data->map[i][j] != ' ')
				return (1); THIS LINE BREAKS EVERYTHING FOR SOME REASON*/
		}
	}
	/* i = -1;
	while (data->check[++i])
	{
		j = -1;
		while (++j < data->grid_w)
			printf("%d", data->check[i][j]);
		printf("\n");
	} */
	return (data->error);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int	i;
	int	j;

	if (argc != 2)
		return (EXIT_FAILURE);
	init_data(&data);
	if (parse_cfg(&data, argv[1]))
		close_handler(&data, "invalid path");
	data.map = get_grid(data.fd);
	if (!data.map)
		close_handler(&data, "can't load map");
	i = -1;
	while (data.map[++i])
		printf("%s\n", data.map[i]);
	set_map_size(&data);
	printf("width: %d height: %d\n", data.grid_w, data.grid_h);
	data.check = init_check_matrix(&data);
	if (parse_map(&data))
	{
		i = -1;
		while (data.check[++i])
		{
			j = -1;
			while (++j < data.grid_w)
				printf("%d", data.check[i][j]);
			printf("\n");
		}
		close_handler(&data, "map misconfigured");
	}
	data.tex_no = init_texture(&data, data.tex_no_path);
	data.tex_so = init_texture(&data, data.tex_so_path);
	data.tex_we = init_texture(&data, data.tex_we_path);
	data.tex_ea = init_texture(&data, data.tex_ea_path);
	init_events(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
