/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_validation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:06:15 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/10/17 00:36:56 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	validate_png(char *path)
{
	int	len;

	if (!path || !path[0] || all_white_spaces(path))
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Empty PNG path", 2);
		return (EXIT_FAILURE);
	}
	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".png", 4) != 0)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Invalid .png file format", 2);
		return (EXIT_FAILURE);
	}
	if (access(path, F_OK) == -1)
		return (error_msg(path), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
