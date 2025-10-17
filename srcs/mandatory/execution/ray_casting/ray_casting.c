/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:13:57 by thi-huon          #+#    #+#             */
/*   Updated: 2025/09/26 05:13:57 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_cam	make_cam(t_player *p)
{
	t_cam	c;
	double	ps;

	c.dirx = cos(p->angle);
	c.diry = sin(p->angle);
	ps = tan((FOV * PI / 180.0) * 0.5);
	c.plx = -c.diry * ps;
	c.ply = c.dirx * ps;
	return (c);
}

void	cast_rays(t_cub *cub)
{
	t_cam	cam;
	t_ddaw	w;
	int		x;
	int		side;

	if (cub == NULL || cub->rays == NULL)
		return ;
	cam = make_cam(&cub->player);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		dda_init(cub, &cam, x, &w);
		dda_run(cub, &w, &side);
		draw_column_and_store(cub, x, &w, side);
		x++;
	}
}
