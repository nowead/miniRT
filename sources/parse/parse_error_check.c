/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:30:16 by mindaewon         #+#    #+#             */
/*   Updated: 2024/09/25 19:41:26 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_coord(char **coord)
{
	int	i;

	if (!coord)
		return (error_return("Error\nInvalid coordinate", PERROR_ON));
	i = 0;
	while (i < 3)
	{
		if (check_float_str(coord[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_vector(char **vector)
{
	int		i;
	t_vec3	vec;

	if (!vector)
		return (error_return("Error\nInvalid vector", PERROR_ON));
	i = 0;
	while (i < 3)
	{
		if (check_float_str(vector[i]))
			return (1);
		i++;
	}
	vec.x = ft_atof(vector[0]);
	vec.y = ft_atof(vector[1]);
	vec.z = ft_atof(vector[2]);
	if (vec.x < -1 || vec.x > 1 || vec.y < -1 || \
	vec.y > 1 || vec.z < -1 || vec.z > 1)
		return (error_return("Error\nVector must be between -1 and 1", \
		PERROR_OFF));
	return (0);
}
	// if (length(vec) != 1)
	// 	return (error_return("Error\nVector must be normalized", PERROR_OFF));

int	check_color(char **color)
{
	int	r;
	int	g;
	int	b;
	int	i;

	if (!color)
		return (error_return("Error\nInvalid color", PERROR_ON));
	i = 0;
	while (i < 3)
	{
		if (check_decimal_str(color[i]))
			return (1);
		i++;
	}
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (error_return("Error\nColor must be between 0 and 255", \
		PERROR_OFF));
	return (0);
}

int	check_decimal_str(char *str)
{
	int	i;

	if (!str)
		return (error_return("Error\nInvalid decimal number", PERROR_OFF));
	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (i == 0 || str[i] != '\0')
		return (error_return("Error\nInvalid decimal number", PERROR_OFF));
	return (0);
}

int	check_float_str(char *str)
{
	int	i;
	int	dot;
	int	diff;

	if (!str)
		return (error_return("Error\nInvalid float number", PERROR_OFF));
	i = 0;
	dot = 0;
	if (str[i] == '-')
		i++;
	diff = i;
	while (ft_isdigit(str[i]) || str[i] == '.')
	{
		if (str[i] == '.')
		{
			dot++;
			diff = i + 1;
		}
		i++;
	}
	if (diff == i || i == 0 || dot > 1 || str[i] != '\0')
		return (error_return("Error\nInvalid float number", PERROR_OFF));
	return (0);
}
