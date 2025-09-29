/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:02:15 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/09/26 03:39:48 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_direction(char c)
{
	if (c == 'N')
		return (PI / 2);
	else if (c == 'S')
		return (3 * PI / 2);
	else if (c == 'W')
		return (PI);
	else if (c == 'E')
		return (2 * PI);
	return (EXIT_SUCCESS);
}

// static int	player_validation(t_cub *cub, int row)
// {
// 	int	col;
// 	int	offset;

// 	col = 0;
// 	while (cub->map.grid[row][col])
// 	{
// 		if (!ft_strchr(" 01NSEW", cub->map.grid[row][col]))
// 			return (err_w_code("Invalid character in map", EXIT_FAILURE));
// 		else if (ft_strchr("NSEW", cub->map.grid[row][col]))
// 		{
// 			if (cub->player.angle > 0)
// 				return (err_w_code("Only 1 player is accepted", EXIT_FAILURE));
// 			offset = (CELL_PX - M_PLAYER_SIZE) / 2;
// 			cub->player.prev_pos = (t_dpoint){col * CELL_PX, row * CELL_PX};
// 			cub->player.cur_pos.x = col * CELL_PX + offset;
// 			cub->player.cur_pos.y = row * CELL_PX + offset;
// 			cub->player.angle = get_direction(cub->map.grid[row][col]);
// 			cub->map.grid[row][col] = '0';
// 		}
// 		col++;
// 	}
// 	return (EXIT_SUCCESS);
// }

// int	grid_validation(t_cub *cub, int fd)
// {
// 	int	row;

// 	row = 0;
// 	if (!dir_ele_done(&cub->map) || !cub->map.grid[0])
// 	{
// 		error_msg("Invalid map");
// 		return (map_err(&cub->map, NULL, fd));
// 	}
// 	while (*cub->map.grid && cub->map.grid[row])
// 	{
// 		if (player_validation(cub, row) == EXIT_FAILURE)
// 			return (map_err(&cub->map, NULL, fd));
// 		row++;
// 	}
// 	if (!cub->player.angle)
// 	{
// 		error_msg("No player found");
// 		return (map_err(&cub->map, NULL, fd));
// 	}
// 	if (!is_closed_map(&cub->map, cub->player.cur_pos))
// 		return (map_err(&cub->map, NULL, fd));
// 	return (EXIT_SUCCESS);
// }


static int	player_validation(t_cub *cub, int row)
{
	int		col;
	char	ch;

	col = 0;
	while (cub->map.grid[row][col])
	{
		ch = cub->map.grid[row][col];
		if (!ft_strchr(" 01NSEW", ch))
			return (err_w_code("Invalid character in map", EXIT_FAILURE));
		if (ft_strchr("NSEW", ch))
		{
			if (cub->player.found)
				return (err_w_code("Only 1 player is accepted", EXIT_FAILURE));
			cub->player.cur_pos.x = col + 0.5;
			cub->player.cur_pos.y = row + 0.5;
			cub->player.prev_pos = (t_dpoint){col + 0.5, row + 0.5};
			cub->player.angle = get_direction(ch);
			cub->player.found = true;
			cub->map.grid[row][col] = '0'; 
		}
		col++;
	}
	return (EXIT_SUCCESS);
}

int	grid_validation(t_cub *cub, int fd)
{
	int		 row;
	t_dpoint start_px;

	row = 0;
	if (!dir_ele_done(&cub->map) || !cub->map.grid[0])
	{
		error_msg("Invalid map");
		return (map_err(&cub->map, NULL, fd));
	}
	while (cub->map.grid[row])
	{
		if (player_validation(cub, row) == EXIT_FAILURE)
			return (map_err(&cub->map, NULL, fd));
		row++;
	}
	if (!cub->player.found)
	{
		error_msg("No player found");
		return (map_err(&cub->map, NULL, fd));
	}
	start_px.x = cub->player.cur_pos.x * CELL_PX;
	start_px.y = cub->player.cur_pos.y * CELL_PX;
	if (!is_closed_map(&cub->map, start_px))
		return (map_err(&cub->map, NULL, fd));
	return (EXIT_SUCCESS);
}
