/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_ray_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:03:37 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/24 16:54:03 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_ray_sphere(t_inter_vars vars)
{
	float		coeff[3];
	float		t[2];

	compute_sphere_quadratic_coefficients(vars.ray, \
	&vars.obj->data.sphere, coeff);
	if (solve_quadratic_equation(coeff, t))
	{
		update_closest_hit(t[0], 0, &vars);
		if (t[0] != t[1])
			update_closest_hit(t[1], 0, &vars);
	}
	return ;
}

void	compute_sphere_quadratic_coefficients(t_ray *ray, \
t_sphere *sphere, float coeff[3])
{
	t_vec3		co;
	t_vec3		d;
	float		r;

	r = sphere->radius;
	d = ray->dir;
	co = subtract_3dpoints(ray->origin, sphere->center);
	coeff[0] = dot(d, d);
	coeff[1] = 2 * dot(co, d);
	coeff[2] = dot(co, co) - (r * r);
}
