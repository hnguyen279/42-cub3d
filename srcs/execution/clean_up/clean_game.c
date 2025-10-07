/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:49:58 by thi-huon          #+#    #+#             */
/*   Updated: 2025/09/26 05:49:58 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

// static void	free_map_grid(t_map *map) // this function have in parsing
// {
// 	int	i;

// 	if (!map || !map->grid)
// 		return ;
// 	i = 0;
// 	while (i < map->max_rows)
// 	{
// 		if (map->grid[i])
// 		{
// 			free(map->grid[i]);
// 			map->grid[i] = NULL;
// 		}
// 		i++;
// 	}
// 	free(map->grid);
// 	map->grid = NULL;
// }

void	cub3d_cleanup(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->mlx)
		mlx_close_window(cub->mlx);
	delete_textures(cub);
	clean_rays(&cub->rays);
	map_cleanup(&cub->map);
	//free_map_grid(&cub->map); in map_cleanup
	if (cub->mlx)
		mlx_terminate(cub->mlx);
}
