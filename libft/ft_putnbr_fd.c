/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <thjonell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:50:46 by thjonell          #+#    #+#             */
/*   Updated: 2021/04/28 15:43:22 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	str[10];

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		i = 0;
		if (n < 0)
		{
			write(fd, "-", 1);
			n *= -1;
		}
		else if (n == 0)
			str[i++] = 48;
		while (n)
		{
			str[i++] = n % 10 + 48;
			n /= 10;
		}
		i--;
		while (i >= 0)
			write(fd, &str[i--], 1);
	}
}
