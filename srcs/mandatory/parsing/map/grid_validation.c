/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:02:15 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/10/12 14:22:58 by thi-mngu         ###   ########.fr       */
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
	int			row;
	t_dpoint	start_px;

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
