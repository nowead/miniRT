/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_cap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:33:22 by damin             #+#    #+#             */
/*   Updated: 2024/09/24 18:35:50 by damin            ###   ########.fr       */
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
