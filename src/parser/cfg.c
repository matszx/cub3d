/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cfg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:30:50 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/10 13:07:42 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* void	free_cfg(char ***cfg)
{
	int	i;

	if (!cfg)
		return ;
	i = -1;
	while (cfg[++i])
		free_split(cfg[i]);
	free(cfg);
} */

int	get_cfg(t_data *data, const char *path)
{
	char		*line;
	int			count;

	data->cfg = malloc(sizeof(char ***) * (CFG_MAX + 1));
	data->fd = open(path, O_RDONLY);
	if (!data->cfg || data->fd < 0)
		return (1);
	line = next_nonempty_line(data->fd);
	count = 0;
	while (line && count < CFG_MAX)
	{
		data->cfg[count++] = ft_split(line, ' ');
		free(line);
		line = next_nonempty_line(data->fd);
	}
	free(line);
	data->cfg[count] = NULL;
	if (count != CFG_MAX)
		return (1);
	return (0);
}
