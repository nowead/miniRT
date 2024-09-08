/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_ray_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:40:55 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/06 21:26:32 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray_hit	intersect_ray_sphere(t_point3d O, t_vector3d D, \
t_sphere *sphere)
{
	float		r;
	float		t1;
	float		t2;
	float		discriminant;
	t_vector3d	CO;
	float		a;
	float		b;
	float		c;
	
	
    r = sphere->radius;
    CO = subtract_3dpoints(O, sphere->center);
    a = dot(D, D);
    b = 2 * dot(CO, D);
    c = dot(CO, CO) - (r * r);

    discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return ((t_ray_hit){FLT_MAX, FLT_MAX});

    t1 = (-b + sqrt(discriminant)) / (2 * a);
    t2 = (-b - sqrt(discriminant)) / (2 * a);
    
    return ((t_ray_hit){t1, t2});
}
