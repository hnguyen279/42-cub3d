/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:49:58 by thi-huon          #+#    #+#             */
/*   Updated: 2025/10/17 01:06:30 by thi-huon         ###   ########.fr       */
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
}

void	cub3d_cleanup(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->mlx)
		mlx_close_window(cub->mlx);
	delete_textures(cub);
	map_cleanup(&cub->map);
	if (cub->mlx)
		mlx_terminate(cub->mlx);
}

void	cub3d_error_clean(t_cub *cub, const char *msg)
{
	if (msg)
	{
		if (mlx_errno)
			ft_printf_fd(2, "Error MLX %s: %s\n\n", msg,
				mlx_strerror(mlx_errno));
		else if (errno)
			ft_printf_fd(2, "Error System %s: %s\n\n", msg, strerror(errno));
		else
			ft_printf_fd(2, "Error: %s\n", msg);
	}
	cub3d_cleanup(cub);
	exit(1);
}
