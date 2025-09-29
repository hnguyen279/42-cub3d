/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:58:02 by thi-huon          #+#    #+#             */
/*   Updated: 2025/09/26 05:58:02 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d_frame_display(t_cub *cub)
{
	if (!cub || !cub->assets.scene)
		return ;
	cast_rays(cub);
	update_minimap_viewport(cub);
}
