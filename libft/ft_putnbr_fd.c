/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:46:19 by damin             #+#    #+#             */
/*   Updated: 2023/10/26 16:21:10 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	write_nbr(int n, int fd)
{
	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
	}
	if (n == 0)
		return ;
	write_nbr(n / 10, fd);
	ft_putchar_fd(((n % 10) + '0'), fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write (fd, "-2147483648", 11);
	else if (n == 0)
		ft_putchar_fd('0', fd);
	else
		write_nbr(n, fd);
}
