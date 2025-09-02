/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:55:22 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/09/02 18:10:59 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_textures(t_cub *cub)
{
	cub->wall_tex.tex = mlx_load_png(WALL);
	if (!cub->wall_tex.tex)
	{
		error_msg("Failed to load wall texture");
		return (EXIT_FAILURE);
	}
	cub->wall_tex.width = cub->wall_tex.tex->width;
	cub->wall_tex.height = cub->wall_tex.tex->height;
	cub->space_tex.tex = mlx_load_png(SPACE);
	if (!cub->space_tex.tex)
	{
		error_msg("Failed to load space texture");
		return (EXIT_FAILURE);
	}
	cub->space_tex.width = cub->space_tex.tex->width;
	cub->space_tex.height = cub->space_tex.tex->height;
	cub->player_tex.tex = mlx_load_png(PLAYER);
	if (!cub->player_tex.tex)
	{
		error_msg("Failed to load player texture");
		return (EXIT_FAILURE);
	}
	cub->player_tex.width = cub->player_tex.tex->width;
	cub->player_tex.height = cub->player_tex.tex->height;
	return (EXIT_SUCCESS);
}

void	cleanup_textures(t_cub *cub)
{
	if (cub->wall_tex.tex)
		mlx_delete_texture(cub->wall_tex.tex);
	if (cub->space_tex.tex)
		mlx_delete_texture(cub->space_tex.tex);
	if (cub->player_tex.tex)
		mlx_delete_texture(cub->player_tex.tex);
}

// Get pixel color from MLX42 texture
unsigned int	get_texture_pixel(t_texture *tex, int x, int y)
{
	uint32_t	offset;

	if (!tex || !tex->tex || !tex->tex->pixels || x < 0 || y < 0 || x >= tex->width || y >= tex->height)
		return (0);
	offset = y * tex->tex->width + x;
	if (offset >= tex->tex->width * tex->tex->height)
		return (0);
	return (tex->tex->pixels[offset]);
}

// Draw a texture to the screen at specific coordinates
void	draw_texture_to_screen(t_cub *cub, t_texture *tex, int x, int y, int width, int height)
{
	if (!tex || !tex->tex || !cub->mlx.img)
		return;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int tex_x = (j * tex->width) / width;
			int tex_y = (i * tex->height) / height;

			unsigned int color = get_texture_pixel(tex, tex_x, tex_y);
			if (color != 0) // Skip transparent pixels
			{
				int screen_x = x + j;
				int screen_y = y + i;

				if (screen_x >= 0 && screen_x < WINDOW_WIDTH &&
					screen_y >= 0 && screen_y < WINDOW_HEIGHT)
				{
					mlx_put_pixel(cub->mlx.img, screen_x, screen_y, color);
				}
			}
		}
	}
}
