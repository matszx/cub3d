/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:00:35 by mcygan            #+#    #+#             */
/*   Updated: 2025/03/31 17:45:34 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	while (i--)
		free(strs[i]);
	free(strs);
}

static size_t	word_count(char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	while (str[i])
		i++;
	count = 0;
	while (i > 0)
	{
		if (str[i - 1] != c && (str[i] == c || !str[i]))
			count++;
		i--;
	}
	return (count);
}

static char	*find_substr(char *str, char c)
{
	size_t	len;
	char	*res;
	size_t	i;

	len = 0;
	while (str[len] != c && str[len])
		len++;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	**ft_split(char const *s, char c)
{
	size_t	wc;
	char	**res;
	size_t	i;

	wc = word_count((char *)s, c);
	res = malloc((wc + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			res[i++] = find_substr((char *)s, c);
			if (!res[i - 1])
				return (free_split(res), NULL);
		}
		while (*s != c && *s)
			s++;
	}
	res[i] = 0;
	return (res);
}
