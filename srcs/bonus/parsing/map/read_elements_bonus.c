/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_elements_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:06:24 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/10/17 00:37:02 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	type_check(char *element)
{
	if (!element)
		return (-1);
	else if (!ft_strcmp(element, "NO"))
		return (NO);
	else if (!ft_strcmp(element, "SO"))
		return (SO);
	else if (!ft_strcmp(element, "WE"))
		return (WE);
	else if (!ft_strcmp(element, "EA"))
		return (EA);
	else if (!ft_strcmp(element, "C"))
		return (C);
	else if (!ft_strcmp(element, "F"))
		return (F);
	else
		return (-1);
}

int	parse_color(t_map *map, char **splitted_line, int ele_type)
{
	char	**rgb;
	int		len;

	if (comma_count(splitted_line[1]) != 2)
		return (err_w_code("Invalid color format", EXIT_FAILURE));
	len = ft_strlen(splitted_line[1]);
	if (len == 0 || splitted_line[1][len - 1] == ',')
		return (err_w_code("Trailing comma", EXIT_FAILURE));
	rgb = ft_split(splitted_line[1], ',');
	if (!rgb)
		return (err_w_code("No RGB found", EXIT_FAILURE));
	if (ft_2d_len(rgb) != 3)
	{
		ft_clean_arr(&rgb);
		return (err_w_code("Invalid number of colors", EXIT_FAILURE));
	}
	if ((ele_type == F && get_color(rgb, &map->f_color) == EXIT_FAILURE)
		|| (ele_type == C && get_color(rgb, &map->c_color) == EXIT_FAILURE))
	{
		ft_clean_arr(&rgb);
		return (EXIT_FAILURE);
	}
	ft_clean_arr(&rgb);
	return (EXIT_SUCCESS);
}

int	assign_element(t_map *map, char **splitted_line, int ele_type)
{
	if (ele_type == C || ele_type == F)
		return (parse_color(map, splitted_line, ele_type));
	if (validate_png(splitted_line[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ele_type == NO)
		map->no = ft_strdup(splitted_line[1]);
	else if (ele_type == SO)
		map->so = ft_strdup(splitted_line[1]);
	else if (ele_type == WE)
		map->we = ft_strdup(splitted_line[1]);
	else if (ele_type == EA)
		map->ea = ft_strdup(splitted_line[1]);
	return (EXIT_SUCCESS);
}

int	parse_element(t_map *map, char **splitted_line, int ele_type)
{
	if ((ele_type == C && map->c_color != 0)
		|| (ele_type == F && map->f_color != 0)
		|| (ele_type == NO && map->no)
		|| (ele_type == SO && map->so)
		|| (ele_type == WE && map->we)
		|| (ele_type == EA && map->ea))
	{
		return (err_w_code("Element is duplicated", EXIT_FAILURE));
	}
	if (assign_element(map, splitted_line, ele_type) == EXIT_FAILURE)
	{
		ft_clean_arr(&splitted_line);
		return (err_w_code("Assigning elements fails", EXIT_FAILURE));
	}
	ft_clean_arr(&splitted_line);
	return (EXIT_SUCCESS);
}

int	read_element(t_map *map, char *line)
{
	char	**splitted_line;
	int		size;
	int		ele_type;

	splitted_line = ft_split(line, ' ');
	if (!splitted_line)
		return (err_w_code("No element found", EXIT_FAILURE));
	size = ft_2d_len(splitted_line);
	if (size != 2)
	{
		ft_clean_arr(&splitted_line);
		return (err_w_code("Each element can have only 2 parts", EXIT_FAILURE));
	}
	ele_type = type_check(splitted_line[0]);
	if (ele_type == -1)
	{
		ft_clean_arr(&splitted_line);
		return (err_w_code("Invalid element type", EXIT_FAILURE));
	}
	return (parse_element(map, splitted_line, ele_type));
}
