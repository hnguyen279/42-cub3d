/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: core <core@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:05:18 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/10/07 22:42:29 by core             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	path_check(char *path)
{
	int	fd;
	int	len;

	if (!path || all_white_spaces(path))
	{
		ft_putendl_fd("Error:\nInvalid map path!", 2);
		return (-1);
	}
	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".cub", 4))
	{
		ft_putendl_fd("Error:\nInvalid .cub file!", 2);
		return (-1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Error:\nFailed to open file", 2);
		return (-1);
	}
	return (fd);
}
