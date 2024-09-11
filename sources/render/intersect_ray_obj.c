/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_ray_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:40:55 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/11 17:04:53 by seonseo          ###   ########.fr       */
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

	t = dot(subtract_3dpoints(obj->data.plane.pos, ray->origin), obj->data.plane.normal) / dot(ray->dir, obj->data.plane.normal);
	if ((t_range.min < t && t < t_range.max) && t < closest_hit->t)
	{
		closest_hit->t = t;
		closest_hit->obj = obj;
	}
    return ;
}
