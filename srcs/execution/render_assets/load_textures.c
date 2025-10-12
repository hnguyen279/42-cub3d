/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:36:34 by thi-huon          #+#    #+#             */
/*   Updated: 2025/09/26 05:36:34 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_image_t	*load_to_image(t_cub *cub, const char *path,
		const char *label)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	if (!path)
		cub3d_error_clean(cub, "Texture path is NULL");
	tex = mlx_load_png(path);
	if (!tex)
		cub3d_error_clean(cub, "Failed to load texture");
	img = mlx_texture_to_image(cub->mlx, tex);
	mlx_delete_texture(tex);
	if (!img)
		cub3d_error_clean(cub, label);
	return (img);
}

void	load_textures(t_cub *cub) //load fail__> add more codition
{
	t_cub3d_assets	*ca;

	ca = &cub->assets;
	ca->player = load_to_image(cub, PLAYER, "player");
	ca->walls[NO] = load_to_image(cub, cub->map.no, "wall NO");
	ca->walls[SO] = load_to_image(cub, cub->map.so, "wall SO");
	ca->walls[EA] = load_to_image(cub, cub->map.ea, "wall EA");
	ca->walls[WE] = load_to_image(cub, cub->map.we, "wall WE");
}
