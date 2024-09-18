/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:01:06 by damin             #+#    #+#             */
/*   Updated: 2024/09/18 19:07:18 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_sphere(char **line, t_obj *sphere)
{
	sphere->type = SPHERE;
	if (parse_3dpoint(line[1], &sphere->data.sphere.center))
		return (1);
	sphere->data.sphere.radius = ft_atof(line[2]) / 2;
	if (check_float_str(line[3]))
		return (1);
	sphere->specular = ft_atof(line[3]);
	if (line[4] && line[4][0] == 'c')
		parse_checkerboard(line[4], &sphere->checkerboard);
	else
	{
		if (parse_color(line[4], &sphere->color))
		return (1);
	}
	return (0);
}

int	set_plane(char **line, t_obj *plane)
{
	plane->type = PLANE;
	if (parse_3dpoint(line[1], &plane->data.plane.pos))
		return (1);
	if (parse_3dvector(line[2], &plane->data.plane.normal))
		return (1);
	if (check_float_str(line[3]))
		return (1);
	plane->specular = ft_atof(line[3]);
	if (line[4] && line[4][0] == 'c')
		parse_checkerboard(line[4], &plane->checkerboard);
	else
	{
		if (parse_color(line[4], &plane->color))
			return (1);
	}
	return (0);
}

int	set_cylinder(char **line, t_obj *obj)
{
	t_cylinder	*cylinder;
	t_cy_side	*side;

	obj->type = CYLINDER;
	cylinder = &obj->data.cylinder;
	side = &cylinder->side;
	if (parse_3dpoint(line[1], &side->center))
		return (1);
	if (parse_3dvector(line[2], &side->axis))
		return (1);
	if ((check_float_str(line[3])) || check_float_str(line[4]) || check_float_str(line[5]))
		return (1);
    side->radius = ft_atof(line[3]) / 2;
    side->height = ft_atof(line[4]);
	obj->specular = ft_atof(line[5]);
	if (line[6] && line[6][0] == 'c')
		parse_checkerboard(line[6], &obj->checkerboard);
	else
	{
		if (parse_color(line[6], &obj->color))
			return (1);	
		cylinder->top_cap.radius = side->radius;
		cylinder->bottom_cap.radius = side->radius;
		cylinder->top_cap.center = add_vector_to_point(side->center, scale_vector(side->axis, side->height));
		cylinder->top_cap.normal = side->axis;
		cylinder->bottom_cap.center = side->center;
		cylinder->bottom_cap.normal = scale_vector(side->axis, -1);
	}
	return (0);
}

int	set_cone(char **line, t_obj *obj)
{
	t_cone		*cone;
	t_co_side	*side;

	obj->type = CONE;
	cone = &obj->data.cone;
	side = &cone->side;
	if (parse_3dpoint(line[1], &side->vertex))
		return (1);
	if (parse_3dvector(line[2], &side->axis))
		return (1);
	if ((check_float_str(line[3])) || check_float_str(line[4]) || check_float_str(line[5]))
		return (1);
	side->radius = ft_atof(line[3]) / 2;
	side->height = ft_atof(line[4]);
	obj->specular = ft_atof(line[5]);
	if (line[6] && line[6][0] == 'c')
		parse_checkerboard(line[6], &obj->checkerboard);
	else
	{
		if (parse_color(line[6], &obj->color))
			return (1);
		cone->bottom_cap.radius = side->radius;
		cone->bottom_cap.center = add_vector_to_point(side->vertex, scale_vector(side->axis, side->height));
		cone->bottom_cap.normal = side->axis;
	}
	return (0);
}
