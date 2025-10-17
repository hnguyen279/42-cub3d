/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:04:51 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/10/17 00:36:46 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	comma_count(char *str)
{
	int	count;
	int	i;

	if (!str)
		return (0);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

void	free_ptr(char **str)
{
	free(*str);
	*str = NULL;
}

bool	dir_ele_done(t_map *map)
{
	return (map->no && map->so && map->we && map->ea
		&& map->f_color != 0 && map->c_color != 0);
}

void	map_cleanup(t_map *map)
{
	if (!map || !map->grid)
		return ;
	if (map->no)
		free_ptr(&map->no);
	if (map->so)
		free_ptr(&map->so);
	if (map->we)
		free_ptr(&map->we);
	if (map->ea)
		free_ptr(&map->ea);
	if (map->grid)
		ft_clean_arr(&map->grid);
}

int	map_err(t_map *map, char *line, int fd)
{
	map_cleanup(map);
	if (line)
		free(line);
	close (fd);
	return (EXIT_FAILURE);
}
