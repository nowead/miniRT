/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_ray_plane.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:40:55 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/17 21:59:28 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_ray_plane(t_inter_vars vars)
{
	float	t;

	if (compute_plane_intersection(vars.ray, &vars.obj->data.plane, &t))
		update_closest_hit(t, 0, &vars);
}

int	compute_plane_intersection(t_ray *ray, t_plane *plane, float *t)
{
	float	d_dot_n;

	d_dot_n = dot(ray->dir, plane->normal);
	if (!d_dot_n)
		return (0);
	*t = dot(subtract_3dpoints(plane->pos, ray->origin), \
	plane->normal) / d_dot_n;
	return (1);
}
