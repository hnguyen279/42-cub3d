#include "cub3d.h"

int	validate_png(char *path)
{
	// Temporarily disabled for testing
	(void)path;
	return (EXIT_SUCCESS);
	
	/*
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
	*/
}
