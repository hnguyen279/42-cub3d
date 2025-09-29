/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:27:26 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/09/11 14:40:51 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	count_words(char *s, char delimiter)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != delimiter && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == delimiter)
		{
			in_word = 0;
		}
		s++;
	}
	return (count);
}
