/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_cap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:33:22 by damin             #+#    #+#             */
/*   Updated: 2024/09/24 14:34:12 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_cylinder_cap(t_cylinder *cylinder)
{
	t_cy_side	*side;
	t_circle	*top_cap;
	t_circle	*bottom_cap;

	side = &cylinder->side;
	top_cap = &cylinder->top_cap;
	bottom_cap = &cylinder->bottom_cap;
	top_cap->radius = side->radius;
	bottom_cap->radius = side->radius;
	top_cap->center = \
	add_vector_to_point(side->center, scale_vector(side->axis, side->height));
	top_cap->normal = side->axis;
	bottom_cap->center = side->center;
	bottom_cap->normal = scale_vector(side->axis, -1);
}

int	set_cone(char **line, t_obj *obj, void *mlx)
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
	if ((check_float_str(line[3])) || check_float_str(line[4]) || \
	check_float_str(line[5]))
		return (1);
	side->radius = ft_atof(line[3]) / 2;
	side->height = ft_atof(line[4]);
	obj->specular = ft_atof(line[5]);
	set_cone_cap(cone);
	if (parse_color_or_texture(line[6], obj, mlx))
		return (1);
	if (line[7] && parse_xpm_file_to_image(line[7], &obj->bumpmap, mlx))
		return (1);
	return (0);
}

void	set_cone_cap(t_cone *cone)
{
	t_co_side	*side;
	t_circle	*bottom_cap;

	side = &cone->side;
	bottom_cap = &cone->bottom_cap;
	bottom_cap->radius = side->radius;
	bottom_cap->center = \
	add_vector_to_point(side->vertex, scale_vector(side->axis, side->height));
	bottom_cap->normal = side->axis;
}
