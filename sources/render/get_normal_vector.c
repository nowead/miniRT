/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:47:24 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/24 21:56:54 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_normal_vector(t_point3 p, t_closest_hit *hit)
{
	t_vec3	n;

	if (hit->obj->type == SPHERE)
		n = get_sphere_normal(p, hit);
	else if (hit->obj->type == PLANE)
		n = get_plane_normal(p, hit);
	else if (hit->obj->type == CYLINDER)
		n = get_cylinder_normal(p, hit);
	else
		n = get_cone_normal(p, hit);
	return (n);
}

t_vec3	get_sphere_normal(t_point3 p, t_closest_hit *hit)
{
	t_obj		*obj;
	t_point2	texture_point;
	t_vec3		geo_normal;

	obj = hit->obj;
	geo_normal = unit_vector(subtract_3dpoints(p, obj->data.sphere.center));
	if (!obj->bumpmap.ptr)
		return (geo_normal);
	texture_point = convert_to_texture_space(p, hit->obj, hit->sub_obj);
	return (apply_bump_map_texture(&obj->bumpmap, texture_point, &geo_normal));
}

t_vec3	get_plane_normal(t_point3 p, t_closest_hit *hit)
{
	t_obj		*obj;
	t_vec3		geo_normal;
	t_point2	texture_point;

	obj = hit->obj;
	geo_normal = hit->obj->data.plane.normal;
	if (!obj->bumpmap.ptr)
		return (geo_normal);
	texture_point = convert_to_texture_space(p, hit->obj, hit->sub_obj);
	return (apply_bump_map_texture(&obj->bumpmap, texture_point, &geo_normal));
}

t_vec3	get_cylinder_normal(t_point3 p, t_closest_hit *hit)
{
	t_vec3		cp;
	t_vec3		q;
	float		m;
	t_vec3		geo_normal;
	t_point2	texture_point;

	if (hit->sub_obj == TOP_CAP)
		geo_normal = hit->obj->data.cylinder.top_cap.normal;
	else if (hit->sub_obj == BOTTOM_CAP)
		geo_normal = hit->obj->data.cylinder.bottom_cap.normal;
	else
	{
		cp = subtract_3dpoints(p, hit->obj->data.cylinder.side.center);
		m = dot(cp, hit->obj->data.cylinder.side.axis);
		q = add_vector_to_point(hit->obj->data.cylinder.side.center, \
		scale_vector(hit->obj->data.cylinder.side.axis, m));
		geo_normal = unit_vector(subtract_3dpoints(p, q));
	}
	if (!hit->obj->bumpmap.ptr)
		return (geo_normal);
	texture_point = convert_to_texture_space(p, hit->obj, hit->sub_obj);
	return (apply_bump_map_texture(&hit->obj->bumpmap, \
	texture_point, &geo_normal));
}

t_vec3	get_cone_normal(t_point3 p, t_closest_hit *hit)
{
	t_cone		*cone;
	t_vec3		vp;
	t_vec3		geo_normal;
	t_point2	texture_point;

	cone = &hit->obj->data.cone;
	if (hit->sub_obj == BOTTOM_CAP)
		geo_normal = hit->obj->data.cone.bottom_cap.normal;
	else
	{
		cone = &hit->obj->data.cone;
		vp = subtract_3dpoints(p, cone->side.vertex);
		geo_normal = unit_vector(cross(vp, cross(vp, cone->side.axis)));
	}
	if (!hit->obj->bumpmap.ptr)
		return (geo_normal);
	texture_point = convert_to_texture_space(p, hit->obj, hit->sub_obj);
	return (apply_bump_map_texture(&hit->obj->bumpmap, \
	texture_point, &geo_normal));
}
