/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:06:58 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/09/02 12:30:00 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	grid_copy_n_padding(t_map *map, char **new_grid)
{
	int	row;
	int	col;
	int	len;

	row = -1;
	if (!map || !map->grid)
		return (EXIT_FAILURE);
    while (map->grid[++row])
    {
		new_grid[row] = (char *)ft_calloc(map->max_cols + 1, sizeof(char));
		if (!new_grid[row])
			return (err_w_code("Grid copy fails", EXIT_FAILURE));
		col = 0;
		len = ft_strlen(map->grid[row]);
		while (col < len && map->grid[row][col])
		{
			new_grid[row][col] = map->grid[row][col];
			col++;
		}
		while (col < map->max_cols)
		{
			new_grid[row][col] = ' ';
			col++;
		}
	}
	return (EXIT_SUCCESS);
}

static int	map_allocation(t_map *map)
{
	char	**new_grid;
	int		map_size;

	if (map->max_cols > map->size)
	{
		map_size = map->size + G_BUFFER;
		new_grid = (char **)ft_calloc(map_size + 1, sizeof(char *));
		if (!new_grid)
			return (EXIT_FAILURE);
		if (grid_copy_n_padding(map, new_grid) == EXIT_FAILURE)
		{
			ft_clean_arr(&new_grid);
			return (EXIT_FAILURE);
		}
		ft_clean_arr(&map->grid);
		map->grid = new_grid;
		map->size = map_size;
	}
	return (EXIT_SUCCESS);
}

int	read_grid(t_map *map, char *line)
{
	int	len;

	if (!map || !line)
		return (EXIT_FAILURE);
	len = ft_strlen(line);
	if (map_allocation(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	map->grid[map->max_rows] = ft_strdup(line);
	if (!map->grid[map->max_rows])
		return (err_w_code("Grid reading fails", EXIT_FAILURE));
	if (len > map->max_cols)
		map->max_cols = len;
	map->max_rows++;
	if (map->max_rows > 120 || map->max_cols > 120)
		return (err_w_code("Map is too large", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}
