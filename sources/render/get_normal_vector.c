/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:47:24 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/18 00:25:31 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_normal_vector(t_point3 p, t_closest_hit *hit)
{
	t_vec3	n;

	if (hit->obj->type == SPHERE)
		n = unit_vector(subtract_3dpoints(p, hit->obj->data.sphere.center));
	else if (hit->obj->type == PLANE)
		n = hit->obj->data.plane.normal;
	else if (hit->obj->type == CYLINDER)
		n = get_cylinder_normal(p, hit);
	else
		n = get_cone_normal(p, hit);
	return (n);
}

t_vec3	get_cylinder_normal(t_point3 p, t_closest_hit *hit)
{
	t_cylinder	*cylinder;
	t_vec3		temp;
	t_vec3		q;
	float		m;

	cylinder = &hit->obj->data.cylinder;
	if (hit->sub_obj == TOP_CAP)
		return (cylinder->top_cap.normal);
	else if (hit->sub_obj == BOTTOM_CAP)
		return (cylinder->bottom_cap.normal);
	else
	{
		temp = subtract_3dpoints(p, hit->obj->data.cylinder.side.center);
        m = dot(temp, hit->obj->data.cylinder.side.axis);
        q = add_vector_to_point(hit->obj->data.cylinder.side.center,\
		 scale_vector(hit->obj->data.cylinder.side.axis, m));
        return (unit_vector(subtract_3dpoints(p, q)));
	}
}

t_vec3	get_cone_normal(t_point3 p, t_closest_hit *hit)
{
	t_cone	*cone;
	t_vec3	vp;

	cone = &hit->obj->data.cone;
	if (hit->sub_obj == BOTTOM_CAP)
		return (hit->obj->data.cone.bottom_cap.normal);
	else
	{
		cone = &hit->obj->data.cone;
		vp = subtract_3dpoints(p, cone->side.vertex);
		return (unit_vector(cross(vp, cross(vp, cone->side.axis))));
	}
}
