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

int	is_wall(const t_map *map, int x, int y)
{
	int	cols;
	char c;

	if (x < 0 || y < 0 || y >= map->max_rows)
		return (1);
	cols = (int)ft_strlen(map->grid[y]);
	if (x >= cols)
		return (1);
	c = map->grid[y][x];
	if (c == '1' || c == ' ') //c == ' '
		return (1);
	return (0);
}
