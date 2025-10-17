/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:58:07 by thi-huon          #+#    #+#             */
/*   Updated: 2025/10/17 00:48:39 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	event_loop_handler(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (!cub || !cub->mlx)
		return ;
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

static void	cub3d_init_rays(t_cub *cub)
{
	int	i;

	i = 0;
	cub->rays = malloc(sizeof(t_ray *) * WINDOW_WIDTH);
	if (!cub->rays)
		cub3d_error_clean(cub, "malloc rays");
	while (i < WINDOW_WIDTH)
	{
		cub->rays[i] = ft_calloc(1, sizeof(t_ray));
		if (!cub->rays[i])
			cub3d_error_clean(cub, "malloc ray");
		i++;
	}
}

void	cub3d_init(t_cub *cub)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cub->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", true);
	if (!cub->mlx)
		cub3d_error_clean(cub, "mlx_init failed");
	cub3d_init_rays(cub);
	cub3d_init_assets(cub);
	if (!mlx_loop_hook(cub->mlx, event_loop_handler, cub))
		cub3d_error_clean(cub, "mlx_loop_hook failed");
	mlx_close_hook(cub->mlx, event_close_handler, cub);
	cub3d_frame_display(cub);
}
