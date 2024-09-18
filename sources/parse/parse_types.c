/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:38:06 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/18 18:24:40 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_3dpoint(char *line, t_point3 *obj_point)
{
	char	**coord;

	coord = ft_split(line, ',');
	if (check_coord(coord))
	{
		free_lists(coord);
		return (1);
	}
	*obj_point = (t_point3){ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2])};
	free_lists(coord);
	return (0);
}

int	parse_3dvector(char *line, t_vec3 *obj_vec)
{
	char	**vector;

	vector = ft_split(line, ',');
	if (check_vector(vector))
	{
		free_lists(vector);
		return (1);
	}
	*obj_vec = unit_vector((t_vec3){ft_atof(vector[0]), ft_atof(vector[1]), ft_atof(vector[2])});
	free_lists(vector);
	return (0);
}

int	parse_color(char *line, t_color *obj_color)
{
	char	**color;

	color = ft_split(line, ',');
	if (check_color(color))
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
