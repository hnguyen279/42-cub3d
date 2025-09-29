/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:19:09 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/09/11 14:40:51 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;
	char	nb;

	num = (long)n;
	if (num < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	if (0 <= num && num <= 9)
	{
		nb = num + '0';
		write(fd, &nb, 1);
		return ;
	}
	ft_putnbr_fd(num / 10, fd);
	nb = num % 10 + '0';
	write(fd, &nb, 1);
}
