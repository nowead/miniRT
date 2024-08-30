/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:46:46 by damin             #+#    #+#             */
/*   Updated: 2023/10/29 19:22:59 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(const char *str, int i)
{
	if ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		return (1);
	return (0);
}

static int	flow(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

static long	check_bound(const char *str, int i, int sign, long num)
{
	long	max;

	max = 922337203685477580;
	if (ft_isdigit(str[i]))
	{
		if (ft_isdigit(str[i + 1]))
			return (flow(sign));
		if (num < max)
			return (sign * ((num * 10) + (str[i] - '0')));
		else if (num == max)
		{
			if (str[i] >= '0' && str[i] <= '7')
				return (sign * ((num * 10) + (str[i] - '0')));
			else if (str[i] >= '8')
				return (flow(sign));
		}
		else if (num > max)
			return (flow(sign));
	}
	return (sign * num);
}

static long	pull_num(const char *str, int pos, int sign)
{
	int		i;
	long	num;
	long	max;

	i = pos;
	num = 0;
	max = 922337203685477580;
	while (ft_isdigit(str[i]) && num < max)
	{
		num = (10 * num) + (str[i] - '0');
		++i;
	}
	num = check_bound(str, i, sign, num);
	return (num);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	while (is_space(str, i))
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		++i;
	}
	num = (int)pull_num(str, i, sign);
	return (num);
}
