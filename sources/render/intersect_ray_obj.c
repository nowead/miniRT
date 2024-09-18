/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_ray_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:40:55 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/18 16:32:59 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_ray_sphere(t_ray *ray, t_obj *obj, t_float_range t_range, \
t_closest_hit *closest_hit)
{
	float	r;
	float	t1;
	float	t2;
	float	discriminant;
	t_vec3	CO;
	float	a;
	float	b;
	float	c;
	
    r = obj->data.sphere.radius;
    CO = subtract_3dpoints(ray->origin, obj->data.sphere.center);
	
    a = dot(ray->dir, ray->dir);
    b = 2 * dot(CO, ray->dir);
    c = dot(CO, CO) - (r * r);
	
    discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
		return ;
	else
	{
		t1 = (-b + sqrt(discriminant)) / (2 * a);
		t2 = (-b - sqrt(discriminant)) / (2 * a);
	}
	
	if ((t_range.min < t1 && t1 < t_range.max) && t1 < closest_hit->t)
	{
		closest_hit->t = t1;
		closest_hit->obj = obj;
	}
	if ((t_range.min < t2 && t2 < t_range.max) && t2 < closest_hit->t)
	{
		closest_hit->t = t2;
		closest_hit->obj = obj;
	}
    return ;
}

void	intersect_ray_plane(t_ray *ray, t_obj *obj, t_float_range t_range, \
t_closest_hit *closest_hit)
{
	float	t;

	t = dot(subtract_3dpoints(obj->data.plane.pos, ray->origin), \
	obj->data.plane.normal) / dot(ray->dir, obj->data.plane.normal);
	if ((t_range.min < t && t < t_range.max) && t < closest_hit->t)
	{
		closest_hit->t = t;
		closest_hit->obj = obj;
	}
    return ;
}

void	intersect_ray_cone(t_ray *ray, t_obj *obj, t_float_range t_range, \
t_closest_hit *closest_hit)
{
	t_cone	*cone;
	float	t1;
	float	t2;

	float	a_;
	float	b_;
	t_vec3	vo;
	t_vec3	v;
	t_vec3	w;
	float	s;

	float	A;
	float	B;
	float	C;
	float	discriminant;

	cone = &obj->data.cone;
	vo = subtract_3dpoints(ray->origin, cone->vertex);
	a_ = dot(vo, cone->axis);
	b_ = dot(ray->dir, cone->axis);
	v = cross(vo, cone->axis);
	w = cross(ray->dir, cone->axis);
	s = cone->height / cone->radius;

	A = (b_ * b_) - (s * s * dot(w, w));
	B = (2 * a_ * b_) - (2 * s * s * dot(v, w));
	C = (a_ * a_) - (s * s * dot(v, v));
	discriminant = B * B - 4 * A * C;

    if (discriminant < 0)
		return ;
	else
	{
		t1 = (-B + sqrt(discriminant)) / (2 * A);
		if (discriminant != 0)
			t2 = (-B - sqrt(discriminant)) / (2 * A);
		else
			t2 = t1;
	}

	if (is_p_within_cone_height(a_, b_, t1, cone))
	{
		if ((t_range.min < t1 && t1 < t_range.max) && t1 < closest_hit->t)
		{
			closest_hit->t = t1;
			closest_hit->obj = obj;
		}
	}
	if (t1 != t2 && is_p_within_cone_height(a_, b_, t2, cone))
	{
		if ((t_range.min < t2 && t2 < t_range.max) && t2 < closest_hit->t)
		{
			closest_hit->t = t2;
			closest_hit->obj = obj;
		}
	}
	return ;
}

int	is_p_within_cone_height(float a_, float b_, float t, t_cone *cone)
{
	if (b_ > 0)
	{
		if (-a_ / b_ <= t && t < (cone->height - a_) / b_)
			return (1);
	}
	else if (b_ < 0)
	{
		if (-a_ / b_ >= t && t > (cone->height - a_) / b_)
			return (1);
	}
	else
	{
		if (0 <= a_ && a_ < cone->height)
			return (1);
	}
	return (0);
}
