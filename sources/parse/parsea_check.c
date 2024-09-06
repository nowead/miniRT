/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsea_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mindaewon <mindaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:30:16 by mindaewon         #+#    #+#             */
/*   Updated: 2024/09/06 14:31:38 by mindaewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int check_vector_range(t_vector3d vec)
{
	if (vec.x < -1 || vec.x > 1 || vec.y < -1 || vec.y > 1 || vec.z < -1 || vec.z > 1)
		return (1);
	return (0);
}

int check_color_range(int r, int g, int b)
{
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (1);
    return (0);
}

int check_color_string(char **color)
{
	int	i;
	int j;
	
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (ft_isdigit(color[i][j]))
			j++;
		if (j == 0 || color[i][j] != '\0')
			return (1);
		i++;
	}
	reutrn (0);
}

int check_num_string(char *str)
{
	int i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (i == 0 || str[i] != '\0')
		return (1);
	return (0);
}

int	check_float_string(char *str)
{
	int i;
	int dot;

	i = 0;
	dot = 0;
	if (str[i] == '-')
		i++;
	while (ft_isdigit(str[i]) || str[i] == '.')
	{
		if (str[i] == '.')
			dot++;
		i++;
	}
	if (i == 0 || dot > 1 || str[i] != '\0')
		return (1);
	return (0);
}