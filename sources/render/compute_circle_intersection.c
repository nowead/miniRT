/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_circle_intersection.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:46:52 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/17 21:46:59 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	compute_circle_intersection(t_ray *ray, t_circle *circle, float *t)
{
	t_point3	p;
	t_vec3		cp;

	if (!compute_plane_intersection(ray, &(t_plane){circle->center, circle->normal}, t))
		return (0);
	p = add_vector_to_point(ray->origin, scale_vector(ray->dir, *t));
	cp = subtract_3dpoints(p, circle->center);
	if (length(cp) <= circle->radius)
		return (1);
	return (0);
}
