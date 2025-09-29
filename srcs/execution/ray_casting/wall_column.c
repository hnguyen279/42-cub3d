/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_blit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:15:43 by thi-huon          #+#    #+#             */
/*   Updated: 2025/09/26 05:15:43 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_wall_column(t_cub *cub, int x, t_col *c)
{
    uint32_t col;
    int ty;
    int y;

    y = 0;
    while (y < c->y0)
        mlx_put_pixel(cub->assets.scene, x, y++, cub->map.c_color);
    while (y <= c->y1) //col so tex_x: fix, tex__pos_y change
    {
        ty = (int)c->tex_pos_y;
        if (ty < 0) 
            ty = 0;
        if (ty >= (int)c->tex->height)
            ty = (int)c->tex->height - 1;
        col = get_tex_color(c->tex, c->tex_x, ty); //get RGBA of pixel in texture coordinates (c->tex_x, ty)
        if ((uint8_t)(col & 0xFF) == 0) //// AA in byte lower (pack_rgba R<<24|G<<16|B<<8|A), if  fully transparent == 0 (lack wall)
            col = pack_rgba(200, 200, 200, 255); // Ex: light gray, if dont add when lack wall (color of windown: black)
        mlx_put_pixel(cub->assets.scene, x, y, col); //add RGBA of pixel to scene
        c->tex_pos_y += c->tex_step_y;
        y++;
    }
    while (y < WINDOW_HEIGHT)
        mlx_put_pixel(cub->assets.scene, x, y++, cub->map.f_color);
}
