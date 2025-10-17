/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:38:27 by thi-huon          #+#    #+#             */
/*   Updated: 2025/09/26 05:38:27 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_buffers(t_cub *cub)
{
	t_cub3d_assets	*ca;

	ca = &cub->assets;
	ca->scene = new_image(cub, WINDOW_WIDTH, WINDOW_HEIGHT);
	ca->ceiling = new_image(cub, WINDOW_WIDTH, WINDOW_HEIGHT / 2);
	ca->floor = new_image(cub, WINDOW_WIDTH, WINDOW_HEIGHT / 2);
}

static void	attach_layers(t_cub *cub)
{
	t_cub3d_assets	*ca;

	ca = &cub->assets;
	if (mlx_image_to_window(cub->mlx, ca->scene, 0, 0) < 0)
		cub3d_error_clean(cub, "scene");
}

static void	place_player_hud(t_cub *cub, int margin)
{
	t_cub3d_assets	*ca;
	int32_t			px;
	int32_t			py;

	ca = &cub->assets;
	if (!ca->player)
		return ;
	px = (WINDOW_WIDTH - (int32_t)ca->player->width) / 2;
	py = WINDOW_HEIGHT - (int32_t)ca->player->height - margin;
	if (mlx_image_to_window(cub->mlx, ca->player, px, py) < 0)
		cub3d_error_clean(cub, "player_hud");
}

void	cub3d_init_assets(t_cub *cub)
{
	load_textures(cub);
	create_buffers(cub);
	attach_layers(cub);
	place_player_hud(cub, -50);
}
