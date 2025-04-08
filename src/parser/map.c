/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:40:45 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/08 16:13:41 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	set_map_size(t_data *data)
{
	int		width;
	int		i;
	int		j;
	
	width = 0;
	i = -1;
	while (data->map[++i])
	{
		j = 0;
		while (data->map[i][j])
			j++;
		if (j > width)
			width = j;
	}
	data->grid_w = width;
	data->grid_h = i;
}

char	**init_check_matrix(t_data *data)
{
	char	**check_matrix;
	int		i;
	int		j;
	
	check_matrix = malloc(sizeof(char *) * (data->grid_h + 1));
	if (!check_matrix)
		return (NULL);
	i = -1;
	while (++i < data->grid_h)
	{
		check_matrix[i] = malloc(sizeof(char) * (data->grid_w + 1));
		if (!check_matrix[i])
		{
			while (i--)
				free(check_matrix[i]);
			return (free(check_matrix), NULL);
		}
		j = -1;
		while (++j < data->grid_w)
			check_matrix[i][j] = 0;
		check_matrix[i][j] = '\n';
	}
	check_matrix[i] = NULL;
	return (check_matrix);
}

static void	recursion(t_data *data, int x, int y)
{
	if (x > 0 && !data->check[y][x - 1])
		parse_cluster(data, x - 1, y);
	if (x < data->grid_w - 1 && !data->check[y][x + 1])
		parse_cluster(data, x + 1, y);
	if (y > 0 && !data->check[y - 1][x])
		parse_cluster(data, x, y - 1);
	if (y < data->grid_h - 1 && !data->check[y + 1][x])
		parse_cluster(data, x, y + 1);
}

int	parse_cluster(t_data *data, int x, int y)
{
	char 		c;
	
	printf("hello1 %d %d\n", x, y);
	c = data->map[y][x];
	printf("hello2\n");
	if (c == '1')
		return (0);
	else if (x == 0 || x == data->grid_w - 1 || y == 0 || y == data->grid_h - 1)
		return (data->error++, 1);
	else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (c != '0')
		{
			if (data->pos_x > 0.0)
				return (data->error++, 1);
			data->pos_x = x + 0.5;
			data->pos_y = y + 0.5;
			data->pos_a = 1.5; // placeholder
		}
		data->check[y][x] = 1;
		recursion(data, x, y);
	}
	else
		return (data->error++, 1);
	return (0);
}
