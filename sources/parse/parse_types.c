/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:38:06 by seonseo           #+#    #+#             */
/*   Updated: 2024/10/01 14:38:17 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_3dpoint(char *line, t_point3 *obj_point)
{
	char	**coord;

	if (!line)
		error_return("Error\nInvalid point", PERROR_ON);
	coord = ft_split(line, ",");
	if (check_coord(coord))
	{
		free_lists(coord);
		return (1);
	}
	*obj_point = (t_point3){ft_atof(coord[0]), \
	ft_atof(coord[1]), ft_atof(coord[2])};
	free_lists(coord);
	return (0);
}

int	parse_3dvector(char *line, t_vec3 *obj_vec)
{
	char	**vector;

	if (!line)
		error_return("Error\nInvalid vector", PERROR_ON);
	vector = ft_split(line, ",");
	if (check_vector(vector))
	{
		free_lists(vector);
		return (1);
	}
	*obj_vec = unit_vector((t_vec3){ft_atof(vector[0]), \
	ft_atof(vector[1]), ft_atof(vector[2])});
	free_lists(vector);
	return (0);
}

int	parse_color(char *line, t_color *obj_color)
{
	char	**color;

	if (!line)
		error_return("Error\nInvalid color", PERROR_ON);
	color = ft_split(line, ",");
	if (check_color(color))
	{
		free_lists(color);
		return (1);
	}
	if (check_decimal_str(color[0]) || check_decimal_str(color[1]) \
	|| check_decimal_str(color[2]))
	{
		free_lists(color);
		return (1);
	}
	obj_color->r = ft_atoi(color[0]);
	obj_color->g = ft_atoi(color[1]);
	obj_color->b = ft_atoi(color[2]);
	free_lists(color);
	return (0);
}
