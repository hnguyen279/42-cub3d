/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_closed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:04:01 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/10/12 14:22:22 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**init_grid(int row, int col)
{
	int		i;
	char	**grid;

	grid = (char **)ft_calloc(row + 1, sizeof(char *));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < row)
	{
		grid[i] = (char *)ft_calloc(col + 1, sizeof(char));
		if (!grid[i])
		{
			ft_clean_arr(&grid);
			return (NULL);
		}
		ft_memset(grid[i], ' ', col);
		i++;
	}
	return (grid);
}

char	**assign_newgrid(t_map *map, int offset)
{
	int		row;
	int		col;
	char	**new_grid;

	new_grid = init_grid(map->max_rows + 2 * offset,
			map->max_cols + 2 * offset);
	if (!new_grid)
	{
		error_msg("Error: Init grid fails");
		return (NULL);
	}
	row = 0;
	while (map && map->grid && map->grid[row])
	{
		col = 0;
		while (map->grid[row][col])
		{
			new_grid[row + offset][col + offset] = map->grid[row][col];
			col++;
		}
		row++;
	}
	return (new_grid);
}

static int	floodfill_player(char **grid, int row, int col)
{
	if (row < 0 || col < 0 || !grid[row]
		|| !grid[row][col] || grid[row][col] == ' ')
		return (1);
	if (grid[row][col] == '1')
		return (0);
	grid[row][col] = '1';
	return (floodfill_player(grid, row - 1, col)
		|| floodfill_player(grid, row + 1, col)
		|| floodfill_player(grid, row, col - 1)
		|| floodfill_player(grid, row, col + 1));
}

static int	floodfill_wall(char **grid, int row, int col)
{
	if (row < 0 || col < 0 || !grid[row]
		|| !grid[row][col] || grid[row][col] == '1')
		return (0);
	if (grid[row][col] == '0')
		return (1);
	grid[row][col] = '1';
	return (floodfill_wall(grid, row - 1, col)
		|| floodfill_wall(grid, row + 1, col)
		|| floodfill_wall(grid, row, col - 1)
		|| floodfill_wall(grid, row, col + 1));
}

bool	is_closed_map(t_map *map, t_dpoint pos)
{
	int		y;
	int		x;
	char	**temp;

	y = (int)(pos.y / CELL_PX) + 1;
	x = (int)(pos.x / CELL_PX) + 1;
	temp = assign_newgrid(map, 1);
	if (!temp)
		return (false);
	if (floodfill_player(temp, y, x) || floodfill_wall(temp, 0, 0))
	{
		ft_clean_arr(&temp);
		return (false);
	}
	ft_clean_arr(&temp);
	temp = assign_newgrid(map, 0);
	if (!temp)
		return (false);
	ft_clean_arr(&temp);
	return (true);
}
