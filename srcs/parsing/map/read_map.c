#include "cub3d.h"

static int	process_line(t_cub *cub, char *line)
{
	if (!line || !line[0] || (line[0] == ' ' && !line[1]))
		return (EXIT_SUCCESS);
	if (!dir_ele_done(&cub->map))
		return (read_element(&cub->map, line));
	else
	{
		if (!line[0] && cub->map.grid && !cub->map.grid[0])
			return (EXIT_SUCCESS);
		else if (!line[0] && cub->map.grid && cub->map.grid[0])
			return (err_w_code("Grid has already started", EXIT_FAILURE));
		return (read_grid(&cub->map, line));
	}
	return (EXIT_SUCCESS);
}

int	read_map(int fd, t_cub *cub)
{
	char	*line;
	int		eof;

	eof = 0;
	cub->map.size = G_BUFFER;
	cub->map.grid = (char **)ft_calloc(cub->map.size + 1, sizeof(char *));
	if (!cub->map.grid)
		return (close (fd), error_msg("Map allocation failed."), EXIT_FAILURE);
	while (1)
	{
		line = ft_readline(fd, &eof);
		if (!line)
			return (EXIT_FAILURE);
		if (eof)
		{
			if (process_line(cub, line) == EXIT_FAILURE)
				return (map_err(&cub->map, line, fd));
			free(line);
			break ;
		}
		if (process_line(cub, line) == EXIT_FAILURE)
			return (map_err(&cub->map, line, fd));
		free(line);
	}
	return (grid_validation(cub, fd));
}