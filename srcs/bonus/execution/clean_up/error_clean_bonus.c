/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_clean_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:54:27 by thi-huon          #+#    #+#             */
/*   Updated: 2025/10/17 00:33:52 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
