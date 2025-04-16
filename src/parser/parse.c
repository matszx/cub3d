/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:54:56 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/16 14:55:22 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	parse_cfg(t_data *data)
{
	int		i;

	i = -1;
	while (++i < CFG_MAX)
	{
		if (data->cfg[i][1] && !data->cfg[i][2])
		{
			if (fill_data(data, data->cfg[i][0], data->cfg[i][1]))
				return (1);
		}
		else
			return (1);
	}
	if (!data->tex_no_path || !data->tex_so_path || \
		!data->tex_we_path || !data->tex_ea_path || \
		data->floor_colour < 0 || data->ceiling_colour < 0)
		return (1);
	return (0);
}

static char	**init_check_matrix(t_data *data)
{
	char	**check_matrix;
	int		i;
	int		j;

	check_matrix = malloc(sizeof(char *) * (data->map_h + 1));
	if (!check_matrix)
		return (NULL);
	i = -1;
	while (++i < data->map_h)
	{
		check_matrix[i] = malloc(sizeof(char) * data->map_w);
		if (!check_matrix[i])
		{
			while (i--)
				free(check_matrix[i]);
			return (free(check_matrix), NULL);
		}
		j = -1;
		while (++j < data->map_w)
			check_matrix[i][j] = 0;
	}
	check_matrix[i] = NULL;
	return (check_matrix);
}

static int	parse_map(t_data *data)
{
	int	i;
	int	j;

	set_map_size(data);
	data->map_check = init_check_matrix(data);
	if (!data->map_check)
		return (1);
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (++j < data->map_w)
		{
			if (!data->map_check[i][j] && (data->map[i][j] == '0'\
				|| data->map[i][j] == 'N' || data->map[i][j] == 'S'\
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E'))
				parse_cluster(data, j, i);
		}
	}
	if (data->pos_x < 0)
		data->error++;
	return (free_matrix(data->map_check), data->error);
}

void	parse(t_data *data)
{
	data->cfg = get_cfg(data);
	if (!data->cfg || parse_cfg(data))
		close_handler(data, "settings misconfigured");
	data->map = get_map(data->fd);
	if (!data->map || parse_map(data))
		close_handler(data, "map misconfigured");
}
