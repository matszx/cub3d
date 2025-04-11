/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:54:56 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/11 12:55:24 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

static int	ft_atoi(const char *str)
{
	long	res;
	int		sign;
	long	last;

	res = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		last = res;
		res = res * 10 + (*str - '0');
		if (res < last)
			return (~sign >> 1);
		str++;
	}
	return (res * sign);
}

static int	str_to_rgb(char *str)
{
	char	**strs;
	int		rgb;

	strs = ft_split(str, 44);
	rgb = ft_atoi(strs[0]) << 16 | ft_atoi(strs[1]) << 8 | ft_atoi(strs[2]);
	return (free_split(strs), rgb);
}

void	free_cfg(char ***cfg)
{
	int	i;

	if (!cfg)
		return ;
	i = -1;
	while (cfg[++i])
		free_split(cfg[i]);
	free(cfg);
}

static char	***get_cfg(t_data *data, const char *path)
{
	int			count;
	char		*line;
	char		***cfg;

	data->fd = open(path, O_RDONLY);
	if (data->fd < 0)
		return (NULL);
	cfg = malloc(sizeof(char ***) * (CFG_MAX + 1));
	if (!cfg)
		return (NULL);
	count = 0;
	line = next_nonempty_line(data->fd);
	while (line && count < CFG_MAX - 1)
	{
		cfg[count++] = ft_split(line, ' ');
		free(line);
		line = next_nonempty_line(data->fd);
	}
	cfg[count++] = ft_split(line, ' ');
	cfg[count] = 0;
	if (count != CFG_MAX)
		return (free(line), NULL);
	return (free(line), cfg);
}

int	parse_cfg(t_data *data, char *path)
{
	int		i;

	data->cfg = get_cfg(data, path);
	if (!data->cfg)
		return (1);
	i = -1;
	while (++i < 6)
	{
		if (!ft_strcmp(data->cfg[i][0], "NO") && data->cfg[i][1] && !data->cfg[i][2] && data->tex_no_path == NULL)
			data->tex_no_path = data->cfg[i][1];
		else if (!ft_strcmp(data->cfg[i][0], "SO") && data->cfg[i][1] && !data->cfg[i][2] && data->tex_so_path == NULL)
			data->tex_so_path = data->cfg[i][1];
		else if (!ft_strcmp(data->cfg[i][0], "WE") && data->cfg[i][1] && !data->cfg[i][2] && data->tex_we_path == NULL)
			data->tex_we_path = data->cfg[i][1];
		else if (!ft_strcmp(data->cfg[i][0], "EA") && data->cfg[i][1] && !data->cfg[i][2] && data->tex_ea_path == NULL)
			data->tex_ea_path = data->cfg[i][1];
		else if (!ft_strcmp(data->cfg[i][0], "F") && data->cfg[i][1] && !data->cfg[i][2] && data->floor_colour == -1)
			data->floor_colour = str_to_rgb(data->cfg[i][1]);
		else if (!ft_strcmp(data->cfg[i][0], "C") && data->cfg[i][1] && !data->cfg[i][2] && data->ceiling_colour == -1)
			data->ceiling_colour = str_to_rgb(data->cfg[i][1]);
		else
			return (1);
	}
	return (0);
}
