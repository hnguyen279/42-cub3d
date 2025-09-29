/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_process_2d.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:06:08 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/09/11 14:40:51 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_process_2d(char **arr, size_t current)
{
	if (!arr[current])
	{
		while (current-- > 0)
		{
			free(arr[current]);
			return ;
		}
		free(*arr);
		*arr = NULL;
	}
}
