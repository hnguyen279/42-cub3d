/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:58:21 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/09/02 11:59:19 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Clear the screen with a background color
void	clear_screen(t_cub *cub)
{
	for (int y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (int x = 0; x < WINDOW_WIDTH; x++)
		{
			mlx_put_pixel(cub->mlx.img, x, y, cub->map.c_color);
		}
	}
}

// Render the map grid with textures
void	render_map_grid(t_cub *cub)
{
	if (!cub->map.grid)
		return;

	int tile_size = 32; // Size of each tile in pixels
	int start_x = 50;   // Starting X position
	int start_y = 50;   // Starting Y position

	for (int row = 0; row < cub->map.max_rows && cub->map.grid[row]; row++)
	{
		int row_len = ft_strlen(cub->map.grid[row]);
		for (int col = 0; col < row_len && col < 1000; col++) // Safety limit
		{
			char cell = cub->map.grid[row][col];
			int x = start_x + col * tile_size;
			int y = start_y + row * tile_size;

			if (cell == '1') // Wall
				draw_texture_to_screen(cub, &cub->wall_tex, x, y, tile_size, tile_size);
			else if (cell == '0') // Space
				draw_texture_to_screen(cub, &cub->space_tex, x, y, tile_size, tile_size);
			else if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W') // Player
			{
				// Draw space first, then player on top
				draw_texture_to_screen(cub, &cub->space_tex, x, y, tile_size, tile_size);
				draw_texture_to_screen(cub, &cub->player_tex, x, y, tile_size, tile_size);
			}
		}
	}

	printf("Map grid rendered successfully!\n");
}

// Render a simple 2D view of the map
int	render_frame(t_cub *cub)
{
	// Clear the screen with ceiling color
	clear_screen(cub);

	// Render the map grid
	render_map_grid(cub);

	return (EXIT_SUCCESS);
}

// Handle window exposure (redraw when window is resized or uncovered)
int	expose_hook(t_cub *cub)
{
	render_frame(cub);
	return (0);
}
