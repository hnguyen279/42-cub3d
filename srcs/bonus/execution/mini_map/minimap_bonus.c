/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:03:57 by thi-huon          #+#    #+#             */
/*   Updated: 2025/10/17 00:34:30 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_minimap_tile(mlx_image_t *img, int x0, int y0, uint32_t c)
{
	int	i;
	int	j;
	int	xx;
	int	yy;

	if (!img)
		return ;
	i = 0;
	while (i < MINI_TILE)
	{
		xx = x0 + i;
		j = 0;
		while (j < MINI_TILE)
		{
			yy = y0 + j;
			if ((unsigned)x0 + i < img->width && (unsigned)y0 + j < img->height)
				mlx_put_pixel(img, xx, yy, c);
			j++;
		}
		i++;
	}
}

static uint32_t	get_minimap_color(char ch)
{
	if (ch == '1')
		return (pack_rgba(0, 0, 255, 255));
	else if (ch == '0' || ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
		return (pack_rgba(200, 200, 200, 255));
	return (pack_rgba(0, 0, 0, 255));
}

void	render_full_map(t_cub *cub)
{
	mlx_image_t	*dst;
	int			my;
	int			mx;
	int			cols;
	char		*row;

	if (!cub || !cub->assets.map || !cub->map.grid)
		return ;
	dst = cub->assets.map;
	fill_image(dst, pack_rgba(0, 0, 0, 255));
	my = -1;
	while (++my < cub->map.max_rows)
	{
		row = cub->map.grid[my];
		if (!row)
			continue ;
		cols = (int)ft_strlen(row);
		mx = -1;
		while (++mx < cols)
			if (row[mx] != ' ')
				draw_minimap_tile(dst, mx * MINI_TILE, my * MINI_TILE,
					get_minimap_color(row[mx]));
	}
}
