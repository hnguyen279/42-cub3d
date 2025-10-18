/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_hit_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:20:44 by thi-huon          #+#    #+#             */
/*   Updated: 2025/10/18 05:59:20 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static double	compute_wall_x(t_cub *cub, t_ddaw *w, int side)
{
	double	hitx;
	double	hity;

	hitx = cub->player.cur_pos.x + w->perp * w->rdx;
	hity = cub->player.cur_pos.y + w->perp * w->rdy;
	if (side == 0)
		return (hity - floor(hity));
	else
		return (hitx - floor(hitx));
}

static mlx_image_t	*pick_tex(t_cub *cub, t_ddaw *w, int side)
{
	if (side == 0)
	{
		if (w->rdx > 0.0)
			return (cub->assets.walls[WE]);
		return (cub->assets.walls[EA]);
	}
	else
	{
		if (w->rdy > 0.0)
			return (cub->assets.walls[SO]);
		return (cub->assets.walls[NO]);
	}
}

static void	column_setup(t_cub *cub, t_ddaw *w, int side, t_col *c)
{
	double	wall_x;
	double	dist;

	dist = w->perp;
	if (w->perp < 1e-6)
		dist = 1e-6;
	c->h = (int)((double)WINDOW_HEIGHT / dist);
	c->y0 = -c->h / 2 + WINDOW_HEIGHT / 2;
	if (c->y0 < 0)
		c->y0 = 0;
	c->y1 = c->h / 2 + WINDOW_HEIGHT / 2;
	if (c->y1 >= WINDOW_HEIGHT)
		c->y1 = WINDOW_HEIGHT - 1;
	c->tex = pick_tex(cub, w, side);
	if (c->tex == NULL)
		return ;
	wall_x = compute_wall_x(cub, w, side);
	c->tex_x = (int)(wall_x * (double)c->tex->width);
	c->tex_step_y = (double)c->tex->height / (double)c->h;
	c->tex_pos_y = (c->y0 - WINDOW_HEIGHT / 2 + c->h / 2) * c->tex_step_y;
}

void	draw_column_and_store(t_cub *cub, int x, t_ddaw *w, int side)
{
	t_col	c;

	column_setup(cub, w, side, &c);
	draw_wall_column(cub, x, &c);
}
