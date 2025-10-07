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



///////////debug

// #include <time.h>

// static double now_ms(void)
// { 
//     struct timespec t; 
//     clock_gettime(CLOCK_MONOTONIC, &t); 
//     return t.tv_sec*1000.0 + t.tv_nsec/1e6; 
// }

// static mlx_image_t *load_to_image(t_cub *cub, const char *path, const char *label)
// {
//     double t0 = now_ms();
//     mlx_texture_t *tex;
//     mlx_image_t *img;

//     if (!path) 
//         cub3d_error_clean(cub, "Texture path is NULL");
//     tex = mlx_load_png(path);
//     if (!tex) 
//         cub3d_error_clean(cub, "Failed to load texture");
//     double t1 = now_ms();

//     img = mlx_texture_to_image(cub->mlx, tex);
//     mlx_delete_texture(tex);
//     if (!img) cub3d_error_clean(cub, label);

//     double t2 = now_ms();
//     printf("%s: PNG decode = %.1f ms, GPU upload = %.1f ms (%ux%u)\n",
//            label, t1 - t0, t2 - t1, img->width, img->height);
//     return img;
// }
////////////////

void	load_textures(t_cub *cub)
{
	t_cub3d_assets	*ca;

	ca = &cub->assets;
	ca->player = load_to_image(cub, PLAYER, "player");
	ca->walls[NO] = load_to_image(cub, cub->map.no, "wall NO");
	ca->walls[SO] = load_to_image(cub, cub->map.so, "wall SO");
	ca->walls[EA] = load_to_image(cub, cub->map.ea, "wall EA");
	ca->walls[WE] = load_to_image(cub, cub->map.we, "wall WE");
}
