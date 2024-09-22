/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_surface_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 21:06:06 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/22 14:07:13 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_surface_color(t_point3 p, t_closest_hit *closest_hit)
{
	t_point2	texture_point;

	if (closest_hit->obj->texture_type == COLOR)
		return (closest_hit->obj->color);
	texture_point = convert_to_texture_space(p, closest_hit->obj, closest_hit->sub_obj);
	if (closest_hit->obj->texture_type == CHECKERBOARD)	
		return (get_checkerboard_color(closest_hit->obj, texture_point));
	else
		return (get_image_color(closest_hit->obj, texture_point));
}

t_point2	convert_to_texture_space(t_point3 p, t_obj *obj, t_sub_obj sub_obj)
{
	t_point2	texture_point; 
	t_vec3		cp;

	texture_point = (t_point2){};
	if (obj->type == SPHERE)
	{
		cp = subtract_3dpoints(p, obj->data.sphere.center);
		texture_point.x = 0.5 - atan2(cp.x, cp.z) / (2 * M_PI);
		texture_point.y = 1 - acos(cp.y / obj->data.sphere.radius) / M_PI;
	}
	else if (obj->type == PLANE)
	{
		cp = subtract_3dpoints(p, obj->data.plane.pos);
		texture_point.x = fmod(cp.x, 1);
		texture_point.y = fmod(cp.z, 1);
	}
	else if (obj->type == CYLINDER)
	{
		cp = world_to_local(p, obj->data.cylinder.side.axis, obj->data.cylinder.side.center);
		if (sub_obj == SIDE)
		{
			texture_point.x = 0.5 - atan2(cp.x, cp.z) / (2 * M_PI);
			texture_point.y = fmod(cp.y, 1);
		}
		else if (sub_obj == TOP_CAP || sub_obj == BOTTOM_CAP)
		{
			texture_point.x = 0.5 - atan2(cp.x, cp.z) / (2 * M_PI); // U 좌표 (각도)
			texture_point.y = sqrt(cp.x * cp.x + cp.z * cp.z); // V 좌표 (반지름에 따라)
		}
	}
	else if (obj->type == CONE)
	{
		cp = world_to_local(p, obj->data.cone.side.axis, obj->data.cone.side.vertex);
		if (sub_obj == SIDE)
		{
			texture_point.x = 0.5 - atan2(cp.x, cp.z) / (2 * M_PI);
			texture_point.y = fmod(-cp.y, 1);
		}
		else if (sub_obj == BOTTOM_CAP)
		{
			texture_point.x = 0.5 - atan2(cp.x, cp.z) / (2 * M_PI); // U 좌표 (각도)
			texture_point.y = sqrt(cp.x * cp.x + cp.z * cp.z); // V 좌표 (반지름에 따라)
		}
	}
	return (texture_point);
}

t_vec3 world_to_local(t_vec3 p, t_vec3 axis, t_point3 center)
{
	t_vec3	local_cp;
	t_vec3	dir;
	t_vec3	cp;
	t_vec3	cp_perp;
	t_vec3	arbitrary_vector;

	dir = unit_vector(axis);
	cp = subtract_3dpoints(p, center);
	local_cp.y = dot(cp, dir);
	cp_perp = subtract_3dpoints(cp, scale_vector(dir, local_cp.y));
	arbitrary_vector = (t_vec3){1, 0, 0};
	if (fabs(dot(dir, arbitrary_vector)) > 0.99)
		arbitrary_vector = (t_vec3){0, 1, 0};
	local_cp.x = dot(cp_perp,unit_vector(cross(dir, arbitrary_vector)));
	local_cp.z = dot(cp_perp, cross(dir, unit_vector(cross(dir, arbitrary_vector))));
	return (local_cp);
}

t_color	get_checkerboard_color(t_obj *obj, t_point2 texture_point)
{
	int		u;
	int		v;
	t_color	checkerboard_color;

	u = floor(texture_point.x * obj->checkerboard.columns);
	v = floor(texture_point.y * obj->checkerboard.rows);
	if ((u + v) % 2 == 0)
		checkerboard_color = obj->checkerboard.color1;
	else
		checkerboard_color = obj->checkerboard.color2;
	return (checkerboard_color);
}

t_color	get_image_color(t_obj *obj, t_point2 texture_point)
{
	t_img	*img;
	int		x;
	int		y;

	img = obj->image;
	x = (int)(texture_point.x * img->width);
	y = (int)(texture_point.x * img->height);
	return (int_to_t_color(my_mlx_get_pixel_color(img, x, y)));
}

t_color	int_to_t_color(int color)
{
	t_color	t_color;

	t_color.r = (color >> 16) & 0xFF;
	t_color.g = (color >> 8) & 0xFF;
	t_color.b = color & 0xFF;
	return (t_color);
}
