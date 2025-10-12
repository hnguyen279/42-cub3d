/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_process_3d.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:16:24 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/10/12 21:17:54 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_process_3d(char ***arr, size_t current)
{
	if (!(arr)[current])
		return ;
	while (current-- > 0)
	{
		ft_free_process_2d(arr[current], current);
		(arr[current]) = NULL;
	}
	free(arr);
	(arr) = NULL;
}
