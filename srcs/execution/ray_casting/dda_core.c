/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:17:38 by thi-huon          #+#    #+#             */
/*   Updated: 2025/09/26 05:17:38 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dda_set_deltas(t_ddaw *w)
{
	if (w->rdx == 0.0)
		w->ddx = DBL_MAX;
	else
		w->ddx = fabs(1.0 / w->rdx); //consfuse
	if (w->rdy == 0.0)
		w->ddy = DBL_MAX;
	else
		w->ddy = fabs(1.0 / w->rdy);
}

static void	dda_set_steps(t_cub *cub, t_ddaw *w)
{
	if (w->rdx < 0.0)
	{
		w->stepx = -1;
		w->sdx = (cub->player.cur_pos.x - w->mx) * w->ddx;
	}
	else
	{
		w->stepx = 1;
		w->sdx = (w->mx + 1.0 - cub->player.cur_pos.x) * w->ddx;
	}
	if (w->rdy < 0.0)
	{
		w->stepy = -1;
		w->sdy = (cub->player.cur_pos.y - w->my) * w->ddy;
	}
	else
	{
		w->stepy = 1;
		w->sdy = (w->my + 1.0 - cub->player.cur_pos.y) * w->ddy;
	}
}

void	dda_init(t_cub *cub, t_cam *cam, int x, t_ddaw *w)
{
	double	cx;

	cx = 2.0 * ((double)x) / (double)WINDOW_WIDTH - 1.0;
	w->rdx = cam->dirx + cam->plx * cx; //formula???
	w->rdy = cam->diry + cam->ply * cx;
	w->mx = (int)floor(cub->player.cur_pos.x);
	w->my = (int)floor(cub->player.cur_pos.y);
	dda_set_deltas(w);
	dda_set_steps(cub, w);
}

void	dda_run(t_cub *cub, t_ddaw *w, int *out_side)
{
	int	side;

	side = 0;
	while (1)
	{
		if (w->sdx < w->sdy)
		{
			w->sdx += w->ddx;
			w->mx += w->stepx;
			side = 0;
		}
		else
		{
			w->sdy += w->ddy;
			w->my += w->stepy;
			side = 1;
		}
		if (is_wall(&cub->map, w->mx, w->my))
			break ;
	}
	*out_side = side;
	if (side == 0)
		w->perp = w->sdx - w->ddx;
	else
		w->perp = w->sdy - w->ddy;
}
