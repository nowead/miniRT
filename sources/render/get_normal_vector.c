/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:47:24 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/23 14:21:48 by damin            ###   ########.fr       */
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

t_vec3	get_sphere_normal(t_point3 p, t_closest_hit *hit)
{
	t_obj		*obj;
	t_point2	texture_point;
	t_vec3		geo_normal;
	t_vec3		bumpmap_normal;

	obj = hit->obj;
		geo_normal = unit_vector(subtract_3dpoints(p, obj->data.sphere.center));
	if (!obj->bumpmap.ptr)
		return (geo_normal);
	texture_point = convert_to_texture_space(p, hit->obj, hit->sub_obj);
	bumpmap_normal = get_bumpmap_normal(&obj->bumpmap, texture_point);
	return (unit_vector(add_3dvectors(geo_normal, bumpmap_normal)));
}

float get_grayscale(t_img *bumpmap, float x, float y)
{
	int color;
	int	r;
	int g;
	int b;
	
	color = my_mlx_get_pixel_color(bumpmap, x, y);
	r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
	// printf("r: %d, g: %d, b: %d\n", r, g, b);
	return (r);
}

// t_vec3	get_bumpmap_normal(t_img *bumpmap, t_point2 texture_point)
// {
// 	t_vec3	bumpmap_normal;
// 	float	height_L;
// 	float	height_R;
// 	float	height_U;
// 	float	height_D;
// 	int		x;
// 	int		y;

// 	x = (int)(texture_point.x * bumpmap->width);
// 	y = (int)(texture_point.y * bumpmap->height);
// 	if (x == 0)
// 		height_L = get_grayscale(bumpmap, x, y) - 0.5;
// 	else
// 		height_L = get_grayscale(bumpmap, x - 1, y) - 0.5;
// 	if (x == bumpmap->width - 1)
// 		height_R = get_grayscale(bumpmap, x, y) - 0.5;
// 	else
// 		height_R = get_grayscale(bumpmap, x + 1, y) - 0.5;
// 	if (y == 0)
// 		height_U = get_grayscale(bumpmap, x, y) - 0.5;
// 	else
// 		height_U = get_grayscale(bumpmap, x, y - 1) - 0.5;
// 	if (y == bumpmap->height - 1)
// 		height_D = get_grayscale(bumpmap, x, y) - 0.5;
// 	else
// 		height_D = get_grayscale(bumpmap, x, y + 1) - 0.5;
// 	bumpmap_normal.x = (height_L - height_R)/2;
// 	bumpmap_normal.y = (height_D - height_U)/2;
// 	bumpmap_normal.z = 0.1;
// 	return (unit_vector(bumpmap_normal));
// }

t_vec3	get_bumpmap_normal(t_img *bumpmap, t_point2 texture_point)
{
	t_vec3	bumpmap_normal;
	float	height_L;
	float	height_R;
	float	height_U;
	float	height_D;
	int		x;
	int		y;

	x = (int)(texture_point.x * bumpmap->width);
	y = (int)(texture_point.y * bumpmap->height);
	if (x == 0)
		height_L = get_grayscale(bumpmap, x, y) - 0.5;
	else
		height_L = get_grayscale(bumpmap, x - 1, y) - 0.5;
	if (x == bumpmap->width - 1)
		height_R = get_grayscale(bumpmap, x, y) - 0.5;
	else
		height_R = get_grayscale(bumpmap, x + 1, y) - 0.5;
	if (y == 0)
		height_U = get_grayscale(bumpmap, x, y) - 0.5;
	else
		height_U = get_grayscale(bumpmap, x, y - 1) - 0.5;
	if (y == bumpmap->height - 1)
		height_D = get_grayscale(bumpmap, x, y) - 0.5;
	else
		height_D = get_grayscale(bumpmap, x, y + 1) - 0.5;
	bumpmap_normal.x = (height_L - height_R)/2;
	bumpmap_normal.y = (height_D - height_U)/2;
	bumpmap_normal.z = 0.1;
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
