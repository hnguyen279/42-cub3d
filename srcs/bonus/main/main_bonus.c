/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:05:21 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/10/17 00:35:27 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	parse_cub_file(char *filename, t_cub *cub)
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

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (ft_printf_fd(2, "Error: %s <map.cub>\n", argv[0]),
			EXIT_FAILURE);
	ft_memset(&cub, 0, sizeof(t_cub));
	if (parse_cub_file(argv[1], &cub) == EXIT_FAILURE)
		cub3d_error_clean(&cub, "parse_cub_file failed");
	cub.map.width = cub.map.max_cols * CELL_PX;
	cub.map.height = cub.map.max_rows * CELL_PX;
	cub3d_init(&cub);
	mlx_loop(cub.mlx);
	cub3d_cleanup(&cub);
	return (0);
}
