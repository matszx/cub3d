/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:54:56 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/09 23:47:25 by mcygan           ###   ########.fr       */
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
	const int	fd = open(path, O_RDONLY);
	char		***cfg;
	int			count;
	char		*line;
	char		**strs;

	if (fd < 0)
		return (NULL);
	data->fd = fd;
	cfg = malloc(sizeof(char ***) * 7);
	if (!cfg)
		return (NULL);
	count = 0;
	line = get_next_line(fd);
	while (line && count < 6)
	{
		strs = ft_split(line, 32);
		if (strs[0][0] != 10)
			cfg[count++] = strs;
		else
			free_split(strs);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	cfg[count] = 0;
	if (count != 6)
		return (NULL);
	return (cfg);
}

int	parse_cfg(t_data *data, char *path)
{
	char	***cfg;
	int		i;

	cfg = get_cfg(data, path);
	if (!cfg)
		return (1);
	i = -1;
	while (++i < 6)
	{
		if (!ft_strcmp(cfg[i][0], "NO") && cfg[i][1] && !cfg[i][2] && data->tex_no_path == NULL)
			data->tex_no_path = cfg[i][1];
		else if (!ft_strcmp(cfg[i][0], "SO") && cfg[i][1] && !cfg[i][2] && data->tex_so_path == NULL)
			data->tex_so_path = cfg[i][1];
		else if (!ft_strcmp(cfg[i][0], "WE") && cfg[i][1] && !cfg[i][2] && data->tex_we_path == NULL)
			data->tex_we_path = cfg[i][1];
		else if (!ft_strcmp(cfg[i][0], "EA") && cfg[i][1] && !cfg[i][2] && data->tex_ea_path == NULL)
			data->tex_ea_path = cfg[i][1];
		else if (!ft_strcmp(cfg[i][0], "F") && cfg[i][1] && !cfg[i][2] && data->floor_colour == -1)
			data->floor_colour = str_to_rgb(cfg[i][1]);
		else if (!ft_strcmp(cfg[i][0], "C") && cfg[i][1] && !cfg[i][2] && data->ceiling_colour == -1)
			data->ceiling_colour = str_to_rgb(cfg[i][1]);
		else
			return (1);
	}
	data->cfg = cfg;
	return (0);
}
