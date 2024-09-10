/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_ray_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:40:55 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/10 14:30:15 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_ray_sphere(t_point3d o, t_vector3d D, t_obj *obj, t_float_range t_range, t_closest_hit *closest_hit)
{
	float		r;
	float		t1;
	float		t2;
	float		discriminant;
	t_vector3d	CO;
	float		a;
	float		b;
	float		c;
	
	
    r = obj->data.sphere.radius;
    CO = subtract_3dpoints(o, obj->data.sphere.center);
    a = dot(D, D);
    b = 2 * dot(CO, D);
    c = dot(CO, CO) - (r * r);

    discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
		t1 = FLT_MAX;
		t2 = FLT_MAX;
	}
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
