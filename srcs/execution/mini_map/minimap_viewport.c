/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_viewport.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:06:46 by thi-huon          #+#    #+#             */
/*   Updated: 2025/09/26 05:06:46 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	clampi(int v, int lo, int hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

static void	minimap_src_xy(t_cub *cub, int wh[2], int xy[2])
{
	int	ppx;
	int	ppy;
	int	x0;
	int	y0;

	ppx = (int)(cub->player.cur_pos.x * MINI_TILE);
	ppy = (int)(cub->player.cur_pos.y * MINI_TILE);
	x0 = ppx - wh[0] / 2;
	y0 = ppy - wh[1] / 2;
	if (wh[0] > (int)cub->assets.map->width)
		wh[0] = (int)cub->assets.map->width;
	if (wh[1] > (int)cub->assets.map->height)
		wh[1] = (int)cub->assets.map->height;
	x0 = clampi(x0, 0, (int)cub->assets.map->width - wh[0]);
	y0 = clampi(y0, 0, (int)cub->assets.map->height - wh[1]);
	xy[0] = x0;
	xy[1] = y0;
}

static void	blit_scaled(mlx_image_t *src, mlx_image_t *dst, int xy[2],
		int wh[2])
{
	int	y;
	int	x;
	int	sx;
	int	sy;

	y = 0;
	while (y < (int)dst->height)
	{
		sy = xy[1] + (int)((int64_t)y * wh[1] / (int)dst->height);
		x = 0;
		while (x < (int)dst->width)
		{
			sx = xy[0] + (int)((int64_t)x * wh[0] / (int)dst->width);
			mlx_put_pixel(dst, x, y, get_tex_color(src, sx, sy));
			x++;
		}
		y++;
	}
}

void	update_minimap_viewport(t_cub *cub)
{
	int	wh[2];
	int	xy[2];

	if (!cub->assets.map || !cub->assets.minimap_img)
		return ;
	wh[0] = MINI_TILES_PER_SIDE * MINI_TILE;
	wh[1] = MINI_TILES_PER_SIDE * MINI_TILE;
	minimap_src_xy(cub, wh, xy);
	blit_scaled(cub->assets.map, cub->assets.minimap_img, xy, wh);
	draw_player_dot(cub, xy, wh);
}
