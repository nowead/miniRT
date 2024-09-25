/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_surface_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 21:06:06 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/24 21:55:46 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_surface_color(t_point3 p, t_closest_hit *hit)
{
	t_obj		*obj;
	t_point2	texture_point;

	obj = hit->obj;
	if (obj->texture_type == COLOR)
		return (obj->color);
	texture_point = convert_to_texture_space(p, obj, hit->sub_obj);
	if (obj->texture_type == CHECKERBOARD)
		return (get_checkerboard_color(&obj->checkerboard, texture_point));
	else
		return (get_image_color(&obj->image, texture_point));
}

t_vec3	world_to_local(t_vec3 p, t_vec3 axis, t_point3 center)
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
	local_cp.x = dot(cp_perp, unit_vector(cross(dir, arbitrary_vector)));
	local_cp.z = dot(cp_perp, \
	cross(dir, unit_vector(cross(dir, arbitrary_vector))));
	return (local_cp);
}

t_color	get_checkerboard_color(t_checkerboard *checkerboard, \
t_point2 texture_point)
{
	int		u;
	int		v;
	t_color	checkerboard_color;

	u = floor(texture_point.x * checkerboard->columns);
	v = floor(texture_point.y * checkerboard->rows);
	if ((u + v) % 2 == 0)
		checkerboard_color = checkerboard->color1;
	else
		checkerboard_color = checkerboard->color2;
	return (checkerboard_color);
}

t_color	get_image_color(t_img *img, t_point2 texture_point)
{
	int		x;
	int		y;

	x = (int)(texture_point.x * img->width);
	y = (int)(texture_point.y * img->height);
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
