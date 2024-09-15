/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:01:06 by damin             #+#    #+#             */
/*   Updated: 2024/09/14 15:39:38 by seonseo          ###   ########.fr       */
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
	if (parse_color(line[4], &sphere->color))
		return (1);
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
	if (parse_color(line[4], &plane->color))
		return (1);
	return (0);
}

int	set_cylinder(char **line, t_obj *cylinder)
{
	cylinder->type = CYLINDER;
	if (parse_3dpoint(line[1], &cylinder->data.cylinder.center))
		return (1);
	if (parse_3dvector(line[2], &cylinder->data.cylinder.axis))
		return (1);
	if ((check_float_str(line[3])) || check_float_str(line[4]) || check_float_str(line[5]))
		return (1);
    cylinder->data.cylinder.radius = ft_atof(line[3]) / 2;
    cylinder->data.cylinder.height = ft_atof(line[4]);
	cylinder->specular = ft_atof(line[5]);
	if (parse_color(line[6], &cylinder->color))
		return (1);
	return (0);
}

int	set_cone(char **line, t_obj *cone)
{
	cone->type = CONE;
	if (parse_3dpoint(line[1], &cone->data.cone.vertex))
		return (1);
	if (parse_3dvector(line[2], &cone->data.cone.axis))
		return (1);
	if ((check_float_str(line[3])) || check_float_str(line[4]) || check_float_str(line[5]))
		return (1);
	cone->data.cone.radius = ft_atof(line[3]) / 2;
	cone->data.cone.height = ft_atof(line[4]);
	cone->specular = ft_atof(line[5]);
	if (parse_color(line[6], &cone->color))
		return (1);
	return (0);
}
