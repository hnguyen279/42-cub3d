/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:58:07 by thi-huon          #+#    #+#             */
/*   Updated: 2025/10/17 00:34:03 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	event_loop_handler(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (!cub || !cub->mlx)
		return ;
	mlx_get_mouse_pos(cub->mlx, &cub->mouse_x, &cub->mouse_y);
	handle_input(cub);
	cub3d_frame_display(cub);
}

static void	event_close_handler(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	cub3d_cleanup(cub);
	exit(0);
}

void	cub3d_init(t_cub *cub)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cub->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", true);
	if (!cub->mlx)
		cub3d_error_clean(cub, "mlx_init failed");
	cub->mouse_x = WINDOW_WIDTH / 2;
	cub->mouse_y = WINDOW_HEIGHT / 2;
	cub->prev_mouse_x = cub->mouse_x;
	cub->prev_mouse_y = cub->mouse_y;
	cub3d_init_assets(cub);
	if (!mlx_loop_hook(cub->mlx, event_loop_handler, cub))
		cub3d_error_clean(cub, "mlx_loop_hook failed");
	mlx_close_hook(cub->mlx, event_close_handler, cub);
	cub3d_frame_display(cub);
}
