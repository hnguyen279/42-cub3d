/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:00:42 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/10/12 13:50:20 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	realloc_buffer(char **buffer, int size)
{
	int		i;
	char	*new_buffer;

	new_buffer = ft_calloc((size + 1), sizeof(char));
	if (!new_buffer)
	{
		free(*buffer);
		*buffer = NULL;
		return ;
	}
	i = 0;
	while ((*buffer)[i])
	{
		new_buffer[i] = (*buffer)[i];
		i++;
	}
	new_buffer[i] = '\0';
	free(*buffer);
	*buffer = new_buffer;
}

static int	process_read(char **line, int fd, int *eof, int size)
{
	int		byte;
	char	c;
	int		index;

	index = 0;
	while (1)
	{
		byte = read(fd, &c, 1);
		if (byte == -1)
			return (err_w_code("Error: Read file fails", EXIT_FAILURE));
		if (byte == 0)
			*eof = 1;
		if (byte == 0 || c == '\n')
			break ;
		(*line)[index++] = c;
		if (index <= size)
		{
			size += G_BUFFER;
			realloc_buffer(line, size);
			if (!*line)
				return (err_w_code("Error: Realloc fails", EXIT_FAILURE));
		}
	}
	(*line)[index] = '\0';
	return (EXIT_SUCCESS);
}

char	*ft_readline(int fd, int *eof)
{
	char	*line;

	line = ft_calloc(G_BUFFER + 1, sizeof(char));
	if (line == NULL)
	{
		error_msg("Error: Readline NULL");
		return (NULL);
	}
	else if (process_read(&line, fd, eof, G_BUFFER) == EXIT_FAILURE)
	{
		free(line);
		error_msg("Error: Readline fails");
		return (NULL);
	}
	return (line);
}
