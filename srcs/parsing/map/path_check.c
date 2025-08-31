#include "cub3d.h"

int	path_check(char *path)
{
	int	fd;
	int	len;

	if (!path || all_white_spaces(path))
	{
		ft_putendl_fd(2, "Error:\nInvalid map path!");
		return (-1);
	}
	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".cub", 4))
	{
		ft_putendl_fd(2, "Error:\nInvalid .cub file!");
		return (-1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd(2, "Error:\nFailed to open file");
		return (-1);
	}
	return (fd);
}
