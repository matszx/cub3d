/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 23:25:54 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/29 12:44:44 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_str_array(char **strs)
{
	size_t	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

int	ft_atoi(const char *str)
{
	long	last;
	long	res;
	int		sign;

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

int	copy_line(char *src, char *dst)
{
	size_t	i;

	i = 0;
	while (src[i] && src[i] != '\n' && i < MAP_MAX)
	{
		dst[i] = src[i];
		i++;
	}
	if (src[i] && src[i] != '\n')
		return (1);
	dst[i] = 0;
	return (0);
}

char	*next_nonempty_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && *line == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}
