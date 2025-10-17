/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:42:49 by thi-huon          #+#    #+#             */
/*   Updated: 2025/10/17 00:51:08 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rotate_and_escape(t_cub *cub)
{
	double	dt;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub->mlx);
		return (1);
	}
	dt = cub->mlx->delta_time;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->player.angle -= ROTATE_SPEED * dt;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->player.angle += ROTATE_SPEED * dt;
	cub->player.angle = norm_angle(cub->player.angle);
	return (0);
}
