/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_surface_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 21:06:06 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/21 21:54:55 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_surface_color(t_point3 p, t_closest_hit *closest_hit)
{
	t_point2	texture_point;

	if (closest_hit->obj->texture_type == COLOR)
		return (closest_hit->obj->color);
	texture_point = p_to_uv(p, closest_hit->obj, closest_hit->sub_obj);
	if (closest_hit->obj->texture_type == CHECKERBOARD)	
		return (map_checkerboard(closest_hit->obj, texture_point));
	else
		return ((t_color){});
}

t_point2	p_to_uv(t_point3 p, t_obj *obj, t_sub_obj sub_obj)
{
	t_point2	texture_point; 
	t_vec3		op;

	texture_point = (t_point2){};
	if (obj->type == SPHERE)
	{
		op = subtract_3dpoints(p, obj->data.sphere.center);
		texture_point.x = 0.5 - atan2(op.x, op.z) / (2 * M_PI);
		texture_point.y = 1 - acos(op.y / obj->data.sphere.radius) / M_PI;
	}
	else if (obj->type == PLANE)
	{
		op = subtract_3dpoints(p, obj->data.plane.pos);
		texture_point.x = fmod(op.x, 1);
		texture_point.y = fmod(op.z, 1);
	}
	else if (obj->type == CYLINDER)
	{
		op = world_to_local(p, obj->data.cylinder.side.axis, obj->data.cylinder.side.center);
		if (sub_obj == SIDE)
		{
			texture_point.x = 0.5 - atan2(op.x, op.z) / (2 * M_PI);
			texture_point.y = fmod(op.y, 1);
		}
		else if (sub_obj == TOP_CAP || sub_obj == BOTTOM_CAP)
		{
			texture_point.x = 0.5 - atan2(op.x, op.z) / (2 * M_PI); // U 좌표 (각도)
			texture_point.y = sqrt(op.x * op.x + op.z * op.z); // V 좌표 (반지름에 따라)
		}
	}
	else if (obj->type == CONE)
	{
		op = world_to_local(p, obj->data.cone.side.axis, obj->data.cone.side.vertex);
		if (sub_obj == SIDE)
		{
			texture_point.x = 0.5 - atan2(op.x, op.z) / (2 * M_PI);
			texture_point.y = fmod(-op.y, 1);
		}
		else if (sub_obj == BOTTOM_CAP)
		{
			texture_point.x = 0.5 - atan2(op.x, op.z) / (2 * M_PI); // U 좌표 (각도)
			texture_point.y = sqrt(op.x * op.x + op.z * op.z); // V 좌표 (반지름에 따라)
		}
	}
	return (texture_point);
}

t_color	map_checkerboard(t_obj *obj, t_point2 texture_point)
{
	int		u;
	int		v;
	t_color	checkerboard_color;

	u = floor(texture_point.x * obj->checkerboard.width);
	v = floor(texture_point.y * obj->checkerboard.height);
	if ((u + v) % 2 == 0)
		checkerboard_color = obj->checkerboard.color1;
	else
		checkerboard_color = obj->checkerboard.color2;
	return (checkerboard_color);
}

t_vec3 world_to_local(t_vec3 p, t_vec3 cylinder_axis, t_point3 cylinder_center)
{
	t_vec3	local_op;
	t_vec3	dir;
	t_vec3	op;
	t_vec3	op_perp;
	t_vec3	arbitrary_vector;

	dir = unit_vector(cylinder_axis);
	op = subtract_3dpoints(p, cylinder_center);
	local_op.y = dot(op, dir);
	op_perp = subtract_3dpoints(op, scale_vector(dir, local_op.y));
	arbitrary_vector = (t_vec3){1, 0, 0};
	if (fabs(dot(dir, arbitrary_vector)) > 0.99)
		arbitrary_vector = (t_vec3){0, 1, 0};
	local_op.x = dot(op_perp,unit_vector(cross(dir, arbitrary_vector)));
	local_op.z = dot(op_perp, cross(dir, unit_vector(cross(dir, arbitrary_vector))));
	return (local_op);
}

// t_color int_to_t_color(int int_color)
// {
// 	t_color color;

// 	color.r = (int_color >> 16) & 0xFF;
// 	color.g = (int_color >> 8) & 0xFF;
// 	color.b = int_color & 0xFF;
// 	return (color);
// }
