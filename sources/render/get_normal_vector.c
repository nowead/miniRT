/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:47:24 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/23 18:30:36 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_normal_vector(t_point3 p, t_closest_hit *hit)
{
	t_vec3	n;

	if (hit->obj->type == SPHERE)
		n = get_sphere_normal(p, hit);
	else if (hit->obj->type == PLANE)
		n = hit->obj->data.plane.normal;
	else if (hit->obj->type == CYLINDER)
		n = get_cylinder_normal(p, hit);
	else
		n = get_cone_normal(p, hit);
	return (n);
}


float get_bump_map_height(t_img *bumpmap, float x, float y)
{
	return (my_mlx_get_pixel_color(bumpmap, x, y) & 0xFF);
}

t_vec3	get_sphere_normal(t_point3 p, t_closest_hit *hit)
{
	t_obj		*obj;
	t_point2	texture_point;
	t_vec3		geo_normal;
	t_vec3		bumpmap_normal;
	t_vec3		u;
	t_vec3		v;
	t_vec3		u_comp;
	t_vec3		v_comp;
	t_vec3		result;

	obj = hit->obj;
		geo_normal = unit_vector(subtract_3dpoints(p, obj->data.sphere.center));
	if (!obj->bumpmap.ptr)
		return (geo_normal);
	texture_point = convert_to_texture_space(p, hit->obj, hit->sub_obj);
	bumpmap_normal = get_bumpmap_normal(&obj->bumpmap, texture_point);
	u = unit_vector(cross((t_vec3){0,1,0}, geo_normal));
	v = cross(geo_normal, u);
	u_comp = scale_vector(u, bumpmap_normal.x);
	v_comp = scale_vector(v, bumpmap_normal.y);
	result = geo_normal;
	result = add_3dvectors(result, u_comp);
	result = add_3dvectors(result, v_comp);
	return (unit_vector(result));
}

t_vec3	get_bumpmap_normal(t_img *bumpmap, t_point2 texture_point)
{
	t_vec3	bumpmap_normal;
	float	height_L;
	float	height_R;
	float	height_U;
	float	height_D;
	int		x;
	int		y;

	x = (int)(texture_point.x * bumpmap->width - 1);
	y = (int)(texture_point.y * bumpmap->height - 1);
	if (x == 0)
		height_L = get_bump_map_height(bumpmap, bumpmap->width - 1, y);
	else
		height_L = get_bump_map_height(bumpmap, x - 1, y);
	if (x == bumpmap->width - 1)
		height_R = get_bump_map_height(bumpmap, 0, y);
	else
		height_R = get_bump_map_height(bumpmap, x + 1, y);
	if (y == 0)
		height_U = get_bump_map_height(bumpmap, x, y);
	else
		height_U = get_bump_map_height(bumpmap, x, y - 1);
	if (y == bumpmap->height - 1)
		height_D = get_bump_map_height(bumpmap, x, y);
	else
		height_D = get_bump_map_height(bumpmap, x, y + 1);
	bumpmap_normal.x = (height_L - height_R) / 10;
	bumpmap_normal.y = (height_D - height_U) / 10;
	bumpmap_normal.z = 1;
	return (unit_vector(bumpmap_normal));
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
