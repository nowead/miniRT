/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_texture_space.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:47:01 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/25 13:51:17 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point2	convert_to_texture_space(t_point3 p, t_obj *obj, t_sub_obj sub_obj)
{
	t_point2	texture_point;

	texture_point = (t_point2){};
	if (obj->type == SPHERE)
		texture_point = convert_sphere_point(p, obj);
	else if (obj->type == PLANE)
		texture_point = convert_plane_point(p, obj);
	else if (obj->type == CYLINDER)
		texture_point = convert_cylinder_point(p, obj, sub_obj);
	else if (obj->type == CONE)
		texture_point = convert_cone_point(p, obj, sub_obj);
	return (texture_point);
}

t_point2	convert_sphere_point(t_point3 p, t_obj *obj)
{
	t_point2	texture_point;
	t_vec3		cp;

	cp = subtract_3dpoints(p, obj->data.sphere.center);
	texture_point.x = 0.5 - atan2(cp.x, cp.z) / (2 * M_PI);
	texture_point.y = acos(cp.y / obj->data.sphere.radius) / M_PI;
	return (texture_point);
}

t_point2	convert_plane_point(t_point3 p, t_obj *obj)
{
	t_point2	texture_point;
	t_vec3		cp;

	cp = subtract_3dpoints(p, obj->data.plane.pos);
	texture_point.x = fmod(cp.x, 1);
	texture_point.y = fmod(cp.z, 1);
	return (texture_point);
}

t_point2	convert_cylinder_point(t_point3 p, t_obj *obj, t_sub_obj sub_obj)
{
	t_point2	texture_point;
	t_vec3		cp;

	cp = world_to_local(p, obj->data.cylinder.side.axis, \
	obj->data.cylinder.side.center);
	if (sub_obj == SIDE)
	{
		texture_point.x = 0.5 - atan2(cp.x, cp.z) / (2 * M_PI);
		texture_point.y = fmod(cp.y, 1);
	}
	else
	{
		texture_point.x = 0.5 - atan2(cp.x, cp.z) / (2 * M_PI);
		texture_point.y = sqrt(cp.x * cp.x + cp.z * cp.z);
	}
	return (texture_point);
}

t_point2	convert_cone_point(t_point3 p, t_obj *obj, t_sub_obj sub_obj)
{
	t_point2	texture_point;
	t_vec3		cp;

	cp = world_to_local(p, obj->data.cone.side.axis, \
	obj->data.cone.side.vertex);
	if (sub_obj == SIDE)
	{
		texture_point.x = 0.5 - atan2(cp.x, cp.z) / (2 * M_PI);
		texture_point.y = fmod(cp.y, 1);
	}
	else
	{
		texture_point.x = 0.5 - atan2(cp.x, cp.z) / (2 * M_PI);
		texture_point.y = 1 - sqrt(cp.x * cp.x + cp.z * cp.z);
	}
	return (texture_point);
}
