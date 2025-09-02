/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:00:20 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/09/02 12:32:07 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_single_color(const char *color)
{
	int	i;
	int	color_value;

	if (!color[0] || ft_strlen(color) > 3)
		return (-1);
	i = 0;
	color_value = 0;
	while (color[i])
	{
		if (color[i] < '0' || color[i] > '9')
			return (-1);
		color_value = color_value * 10 + color[i] - '0';
		i++;
	}
	return (color_value);
}

int	get_color(char **rgb_colors, int *ceil_or_floor)
{
	int	red;
	int	green;
	int	blue;

	red = get_single_color(rgb_colors[0]);
	green = get_single_color(rgb_colors[1]);
	blue = get_single_color(rgb_colors[2]);
	if (red == -1 || green == -1 || blue == -1)
		return (err_w_code("Invalid color value", EXIT_FAILURE));
	if (red > 255 || green > 255 || blue > 255)
		return (err_w_code("Color value out of range (0-255)", EXIT_FAILURE));
	*ceil_or_floor = (red << 16) + (green << 8) + blue;
	return (EXIT_SUCCESS);
}
