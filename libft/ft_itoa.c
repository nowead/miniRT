/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:00:37 by damin             #+#    #+#             */
/*   Updated: 2023/10/29 19:54:55 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(int n)
{
	int	len;

	len = 2;
	if (n == -2147483648)
		return (12);
	if (n < 0)
	{
		n *= -1;
		++len;
	}
	while (n >= 10)
	{
		n /= 10;
		++len;
	}
	return (len);
}

static void	make_abs(int *n, char *num)
{
	if (*n < 0)
	{
		num[0] = '-';
		*n *= -1;
	}
}

static void	make_num(int n, char *num, int len)
{
	while (n)
	{
		num[--len] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*num;
	int		len;

	len = numlen(n);
	num = (char *)malloc(len * sizeof(char));
	if (!num)
		return (NULL);
	num[--len] = '\0';
	if (n == 0)
	{
		num[0] = '0';
		return (num);
	}
	else if (n == -2147483648)
	{
		num[10] = '8';
		n /= 10;
		--len;
	}
	make_abs(&n, num);
	make_num(n, num, len);
	return (num);
}
