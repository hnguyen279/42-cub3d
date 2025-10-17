/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:08:38 by thi-huon          #+#    #+#             */
/*   Updated: 2025/10/17 00:34:35 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	player_minimap_center(t_cub *cub, int xy[2], int wh[2], int out[2])
{
	int		ppx;
	int		ppy;
	float	rpx;
	float	rpy;

	ppx = (int)(cub->player.cur_pos.x * MINI_TILE);
	ppy = (int)(cub->player.cur_pos.y * MINI_TILE);
	rpx = (ppx - xy[0]) / (float)wh[0];
	rpy = (ppy - xy[1]) / (float)wh[1];
	out[0] = (int)(rpx * (int)cub->assets.minimap_img->width);
	out[1] = (int)(rpy * (int)cub->assets.minimap_img->height);
}

static void	draw_filled_circle(mlx_image_t *ov, int c[2], int r, uint32_t col)
{
	int	dy;
	int	dx;
	int	px;
	int	py;

	dy = -r;
	while (dy <= r)
	{
		dx = -r;
		while (dx <= r)
		{
			if (dx * dx + dy * dy <= r * r)
			{
				px = c[0] + dx;
				py = c[1] + dy;
				if ((unsigned)px < ov->width && (unsigned)py < ov->height)
					mlx_put_pixel(ov, px, py, col);
			}
			dx++;
		}
		dy++;
	}
}

void	draw_player_dot(t_cub *cub, int xy[2], int wh[2])
{
	mlx_image_t	*ov;
	int			center[2];
	uint32_t	col;
	int			r;

	ov = cub->assets.minimap_img;
	player_minimap_center(cub, xy, wh, center);
	col = pack_rgba(220, 40, 40, 255);
	r = 5;
	draw_filled_circle(ov, center, r, col);
}
