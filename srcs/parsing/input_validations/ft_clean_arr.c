#include "cub3d.h"

void    ft_clean_arr(char ***arr)
{
    int i;

    if (!arr || !*arr)
    {
        return ;
    }
    i = 0;
    while ((*arr)[i])
    {
        free((*arr)[i]);
        (*arr)[i] = NULL;
        i++;
    }
    free(*arr);
    (*arr) = NULL;
}
