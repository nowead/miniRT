/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:35:00 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/16 16:36:14 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_closest_hit	closest_intersection(t_ray ray, t_float_range t_range, t_scene *scene)
{
	t_closest_hit	closest_hit;
	t_obj			*obj;

	closest_hit.t = t_range.max;
    closest_hit.obj = NULL;
	obj = scene->obj;
    while (obj)
    {
		if (obj->type == SPHERE)
        	intersect_ray_sphere((t_inter_vars){&ray, obj, &t_range, &closest_hit});
		else if (obj->type == PLANE)
			intersect_ray_plane((t_inter_vars){&ray, obj, &t_range, &closest_hit});
		else if (obj->type == CYLINDER)
			intersect_ray_cylinder(&ray, obj, t_range, &closest_hit);
		else if (obj->type == CONE)
			intersect_ray_cone((t_inter_vars){&ray, obj, &t_range, &closest_hit});
		obj = obj->next;
	}
	return (closest_hit);
}

int	solve_quadratic_equation(float coeff[3], float t[2])
{
	float	discriminant;

	discriminant = coeff[1] * coeff[1] - 4 * coeff[0] * coeff[2];

    if (discriminant < 0)
		return (0);
	else
	{
		t[0] = (-coeff[1] + sqrt(discriminant)) / (2 * coeff[0]);
		if (discriminant != 0)
			t[1] = (-coeff[1] - sqrt(discriminant)) / (2 * coeff[0]);
		else
			t[1] = t[0];
		return (1);
	}
}

void	update_closest_hit(float t, t_sub_obj sub_obj, t_inter_vars *vars)
{
	if ((vars->t_range->min < t && t < vars->t_range->max) && t < vars->closest_hit->t)
	{
		vars->closest_hit->t = t;
		vars->closest_hit->obj = vars->obj;
		vars->closest_hit->sub_obj = sub_obj;
	}
}
