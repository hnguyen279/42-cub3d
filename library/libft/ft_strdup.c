/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:32:44 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/09/11 14:40:51 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*src;
	char	*str_dup;

	src = (char *)s;
	i = 0;
	while (src[i] != '\0')
		i++;
	str_dup = (char *)malloc((i + 1) * sizeof(char));
	if (str_dup == NULL)
		return (NULL);
	i = 0;
	while (str_dup != NULL && src[i] != '\0')
	{
		str_dup[i] = src[i];
		i++;
	}
	str_dup[i] = '\0';
	return (str_dup);
}
