/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 06:12:55 by thi-huon          #+#    #+#             */
/*   Updated: 2025/09/26 06:12:55 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	norm_angle(double a)
{
	double	two_pi;

	two_pi = 2.0 * PI;
	while (a >= two_pi)
		a -= two_pi;
	while (a < 0.0)
		a += two_pi;
	return (a);
}

int	is_wall(t_map *map, double x, double y)
{
	int		map_x;
	int		map_y;
	char	c;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= map->max_cols || map_y < 0
		|| map_y >= map->max_rows)
		return (1);
	c = map->grid[map_y][map_x];
	if (c == '1' || c == ' ') //c == ' '
		return (1);
	return (0);
}