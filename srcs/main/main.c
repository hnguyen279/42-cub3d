/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:05:21 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/09/02 18:05:49 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_cub(t_cub *cub)
{
	cub->map.no = NULL;
	cub->map.so = NULL;
	cub->map.we = NULL;
	cub->map.ea = NULL;
	cub->map.f_color = 0;
	cub->map.c_color = 0;
	cub->map.grid = NULL;
	cub->map.size = 0;
	cub->map.width = 0;
	cub->map.height = 0;
	cub->map.max_cols = 0;
	cub->map.max_rows = 0;
	cub->mlx.mlx = NULL;
	cub->mlx.img = NULL;
	cub->wall_tex.tex = NULL;
	cub->space_tex.tex = NULL;
	cub->player_tex.tex = NULL;
	cub->player.cur_pos.x = 0;
	cub->player.cur_pos.y = 0;
	cub->player.prev_pos.x = 0;
	cub->player.prev_pos.y = 0;
	cub->player.angle = 0;
	cub->player.attack = 0;
}

int	init_mlx(t_cub *cub)
{
	printf("Initializing MLX42...\n");
	cub->mlx.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", true);
	if (!cub->mlx.mlx)
	{
		error_msg("MLX42 initialization failed");
		return (EXIT_FAILURE);
	}
	cub->mlx.img = mlx_new_image(cub->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub->mlx.img)
	{
		error_msg("Image creation failed");
		return (EXIT_FAILURE);
	}
	printf("MLX42 initialized successfully!\n");
	printf("Window size: %dx%d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
	return (EXIT_SUCCESS);
}

void	cleanup_mlx(t_cub *cub)
{
	if (cub->mlx.img)
		mlx_delete_image(cub->mlx.mlx, cub->mlx.img);
	if (cub->mlx.mlx)
		mlx_terminate(cub->mlx.mlx);
}

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(cub->mlx.mlx);
	}
}

int	parse_cub_file(char *filename, t_cub *cub)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		error_msg("Cannot open file");
		return (EXIT_FAILURE);
	}
	if (read_map(fd, cub) == EXIT_FAILURE)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

void	cleanup_cub(t_cub *cub)
{
	if (cub->map.no)
		free(cub->map.no);
	if (cub->map.so)
		free(cub->map.so);
	if (cub->map.we)
		free(cub->map.we);
	if (cub->map.ea)
		free(cub->map.ea);
	if (cub->map.grid)
		ft_clean_arr(&cub->map.grid);
	if (cub->mlx.mlx)
	{
		cleanup_textures(cub);
		cleanup_mlx(cub);
	}
}

static int cleanup_w_err(t_cub cub, char *msg)
{
	error_msg(msg);
	cleanup_cub(&cub);
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
	{
		error_msg("Usage: ./cub3d <map_file.cub>");
		return (EXIT_FAILURE);
	}
	init_cub(&cub);
	if (parse_cub_file(argv[1], &cub) == EXIT_FAILURE)
		return (cleanup_w_err("Failed to parse cub file"));
	printf("File parsed successfully!\n");
	if (init_mlx(&cub) == EXIT_FAILURE)
		return (cleanup_w_err("Graphics initialization failed"));
	if (load_textures(&cub) == EXIT_FAILURE)
		return (cleanup_w_err("Texture loading failed"));
	if (render_frame(&cub) == EXIT_FAILURE)
		return (cleanup_w_err("Rendering failed"));
	if (mlx_image_to_window(cub.mlx.mlx, cub.mlx.img, 0, 0) == -1)
		return (cleanup_w_err("Failed to display image"));
	mlx_key_hook(cub.mlx.mlx, key_hook, &cub);
	fflush(stdout);
	mlx_loop(cub.mlx.mlx);
	fflush(stdout);
	cleanup_cub(&cub);
	return (EXIT_SUCCESS);
}
