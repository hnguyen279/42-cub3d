#include "cub3d.h"

int ft_2d_len(char **arr)
{
    int len;

    len = 0;
    if (!arr)
        return (0);
    while (arr[len])
        len++;
    return (len);
}

int all_white_spaces(char *str)
{
    int i;

    if (!str)
        return (1);
    i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && (str[i] < 9 || str[i] > 13))
            return (0);
        i++;
    }
    return (1);
}
