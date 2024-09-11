/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:01:06 by damin             #+#    #+#             */
/*   Updated: 2024/09/11 15:41:26 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_sphere(char **line, t_obj *sphere)
{
	char	**coord;
	char	**color;

	coord = ft_split(line[1], ',');
	if (check_coord(coord))
		return (1);
	sphere->data.sphere.center = (t_point3){ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2])};
	free_lists(coord);
	
	sphere->data.sphere.radius = ft_atoi(line[2]) / 2;
	
	if (check_float_str(line[3]))
		return (1);
	sphere->specular = ft_atof(line[3]);
	
	color = ft_split(line[4], ',');
	if (check_color(color))
		return (1);
	sphere->color = get_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	free_lists(color);
	
	sphere->next = NULL;
	return (0);
}

int	set_plane(char **line, t_obj *plane)
{
	char	**coord;
	char	**vector;
	char	**color;

	plane->type = PLANE;

	coord = ft_split(line[1], ',');
	if (check_coord(coord))
		return (1);
	plane->data.plane.pos = (t_point3){ft_atoi(coord[0]), ft_atoi(coord[1]), ft_atoi(coord[2])};
	free_lists(coord);

	vector = ft_split(line[2], ',');
	if (check_vector(vector))
		return (1);
	plane->data.plane.normal = (t_vec3){ft_atof(vector[0]), ft_atof(vector[1]), ft_atof(vector[2])};
	free_lists(vector);

	if (check_float_str(line[3]))
		return (1);
	plane->specular = ft_atof(line[3]);

	color = ft_split(line[4], ',');
	if (check_color(color))
		return (1);
	plane->color = get_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	free_lists(color);

	plane->next = NULL;
	return (0);
}

int	set_cylinder(char **line, t_obj *cylinder)
{
    char    **coord;
    char    **vector;
	char	**color;

	cylinder->type = CYLINDER;
	
    coord = ft_split(line[1], ',');
	if (check_coord(coord))
		return (1);
    cylinder->data.cylinder.center = (t_point3){ft_atoi(coord[0]), ft_atoi(coord[1]), ft_atoi(coord[2])};
    free_lists(coord);
	
    vector = ft_split(line[2], ',');
	if (check_vector(vector))
		return (1);
    cylinder->data.cylinder.vector = (t_vec3){ft_atoi(vector[0]), ft_atoi(vector[1]), ft_atoi(vector[2])};
    free_lists(vector);
	
	if ((check_float_str(line[3])) || check_float_str(line[4]) || check_float_str(line[5]))
		return (1);
    cylinder->data.cylinder.radius = ft_atoi(line[3]) / 2;
    cylinder->data.cylinder.height = ft_atoi(line[4]);
	cylinder->specular = ft_atof(line[5]);

	color = ft_split(line[6], ',');
	if (check_color(color))
		return (1);
	cylinder->color = get_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	free_lists(color);
	
	cylinder->next = NULL;
	return (0);
}
