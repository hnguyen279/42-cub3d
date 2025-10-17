/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_game_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:49:58 by thi-huon          #+#    #+#             */
/*   Updated: 2025/10/17 00:33:43 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	delete_img(mlx_t *mlx, mlx_image_t **img)
{
	if (img && *img)
	{
		mlx_delete_image(mlx, *img);
		*img = NULL;
	}
}

static void	delete_textures(t_cub *cub)
{
	delete_img(cub->mlx, &cub->assets.walls[NO]);
	delete_img(cub->mlx, &cub->assets.walls[SO]);
	delete_img(cub->mlx, &cub->assets.walls[EA]);
	delete_img(cub->mlx, &cub->assets.walls[WE]);
	delete_img(cub->mlx, &cub->assets.player);
	delete_img(cub->mlx, &cub->assets.ceiling);
	delete_img(cub->mlx, &cub->assets.floor);
	delete_img(cub->mlx, &cub->assets.scene);
	delete_img(cub->mlx, &cub->assets.minimap_img);
	delete_img(cub->mlx, &cub->assets.minimap_bg);
	delete_img(cub->mlx, &cub->assets.map);
}

static void	clean_rays(t_ray ***rays)
{
	int	i;

	i = 0;
	if (!rays || !(*rays))
		return ;
	while (i < WINDOW_WIDTH)
	{
		if ((*rays)[i])
		{
			free((*rays)[i]);
			(*rays)[i] = NULL;
		}
		i++;
	}
	free(*rays);
	*rays = NULL;
}

void	cub3d_cleanup(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->mlx)
		mlx_close_window(cub->mlx);
	delete_textures(cub);
	clean_rays(&cub->rays);
	map_cleanup(&cub->map);
	if (cub->mlx)
		mlx_terminate(cub->mlx);
}
