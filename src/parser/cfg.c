/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cfg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:30:50 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/16 09:45:35 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_cfg(char ***cfg)
{
	int	i;

	if (!cfg)
		return ;
	i = -1;
	while (cfg[++i])
		free_matrix(cfg[i]);
	free(cfg);
}

static char	***get_cfg(t_data *data, const char *path)
{
	int			count;
	char		*line;
	char		***cfg;

	cfg = malloc(sizeof(char ***) * (CFG_MAX + 1));
	data->fd = open(path, O_RDONLY);
	if (!cfg || data->fd < 0)
		return (free(cfg), NULL);
	line = next_nonempty_line(data->fd);
	count = 0;
	while (line && count < CFG_MAX - 1)
	{
		cfg[count++] = ft_split(line, ' ');
		free(line);
		line = next_nonempty_line(data->fd);
	}
	if (line)
		cfg[count++] = ft_split(line, ' ');
	cfg[count] = 0;
	if (count != CFG_MAX)
		return (free(line), free(cfg), NULL);
	return (free(line), cfg);
}

static int	str_to_rgb(char *str)
{
	char	**strs;
	int		rgb;

	strs = ft_split(str, ',');
	rgb = ft_atoi(strs[0]) << 16 | ft_atoi(strs[1]) << 8 | ft_atoi(strs[2]);
	return (free_matrix(strs), rgb);
}

static int	fill_data(t_data *data, char *s1, char *s2)
{
	if (ft_strcmp(s1, "NO") && !data->tex_no_path)
		data->tex_no_path = s2;
	else if (ft_strcmp(s1, "SO") && !data->tex_so_path)
		data->tex_so_path = s2;
	else if (ft_strcmp(s1, "WE") && !data->tex_we_path)
		data->tex_we_path = s2;
	else if (ft_strcmp(s1, "EA") && !data->tex_ea_path)
		data->tex_ea_path = s2;
	else if (ft_strcmp(s1, "F") && data->floor_colour == -1)
		data->floor_colour = str_to_rgb(s2);
	else if (ft_strcmp(s1, "C") && data->ceiling_colour == -1)
		data->ceiling_colour = str_to_rgb(s2);
	else
		return (1);
	return (0);
}

int	parse_cfg(t_data *data, char *path)
{
	int		i;

	data->cfg = get_cfg(data, path);
	if (!data->cfg)
		return (1);
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
	return (0);
}
