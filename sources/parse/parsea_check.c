/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsea_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mindaewon <mindaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:30:16 by mindaewon         #+#    #+#             */
/*   Updated: 2024/09/07 15:16:10 by mindaewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_coord(char **coord)
{
	int			i;
	t_point3d	point;
	
	i = 0;
	while (i < 3)
	{
		if (check_float_string(coord[i]))
			return (1);
		i++;
	}
	point.x = ft_atof(coord[0]);
	point.y = ft_atof(coord[1]);
	point.z = ft_atof(coord[2]);
	if (point.x < -FLT_MAX || point.x > FLT_MAX || point.y < -FLT_MAX || point.y > FLT_MAX || point.z < -FLT_MAX || point.z > FLT_MAX)
		return (1);
	return (0);
}

int check_vector(char **vector)
{
	int			i;
	t_vector3d	vec;
	
	i = 0;
	while (i < 3)
	{
		if (check_float_string(vector[i]))
			return (1);
		i++;
	}
	vec.x = ft_atof(vector[0]);
	vec.y = ft_atof(vector[1]);
	vec.z = ft_atof(vector[2]);
	if (vec.x < -1 || vec.x > 1 || vec.y < -1 || vec.y > 1 || vec.z < -1 || vec.z > 1)
		return (1);
	return (0);
}

int check_color(char **color)
{
	int r;
	int g;
	int b;
	int i;

	i = 0;
	while (i < 3)
	{
		if (check_num_string(color[i]))
			return (1);
		i++;
	}
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	return (0);
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