/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:50:06 by damin             #+#    #+#             */
/*   Updated: 2024/09/08 21:45:55 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int get_color(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	return (r << 16 | g << 8 | b);
}

float ft_atof(char *str)
{
	float res;
	float sign;
	float dec;
	int i;

	res = 0;
	sign = 1;
	dec = 0;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		res = res * 10 + str[i++] - '0';
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i++] - '0';
		dec++;
	}
	while (dec--)
		res /= 10;
	return (res * sign);
}

int	ft_strslen(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

void free_lists(char **lists)
{
    char **temp = lists;

    if (lists == NULL)
        return;
    while (*temp)
        free(*temp++);
    free(lists);
}