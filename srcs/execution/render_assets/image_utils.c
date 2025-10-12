/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:33:37 by thi-huon          #+#    #+#             */
/*   Updated: 2025/09/26 05:33:37 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*new_image(t_cub *cub, uint32_t w, uint32_t h)
{
	mlx_image_t	*img;

	img = mlx_new_image(cub->mlx, w, h);
	if (!img)
		cub3d_error_clean(cub, "mlx_new_image failed");
	return (img);
}

void	fill_image(mlx_image_t *img, uint32_t color)
{
	uint32_t	y;
	uint32_t	x;

	y = 0;
	if (!img)
		return ;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

uint32_t	pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | a);
}

uint32_t	get_tex_color(mlx_image_t *img, int tex_x, int tex_y)
{
	uint8_t	*p;

	if (!img)
		return (0);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_x >= (int)img->width)
		tex_x = (int)img->width - 1;
	if (tex_y >= (int)img->height)
		tex_y = (int)img->height - 1;
	p = &img->pixels[(tex_y * img->width + tex_x) * 4];
	return (pack_rgba(p[0], p[1], p[2], p[3]));
}
