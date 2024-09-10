/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:39:48 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/10 21:06:09 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	compute_lighting(t_point3d p, t_vector3d v, t_sphere *sphere, t_scene *scene)
{
	t_light			*light;
	t_closest_hit	closest_hit;
	t_vector3d		n;
	t_vector3d		l;
	// t_vector3d		r;
	float			ratio;
	float			n_dot_l;
	// float			r_dot_v;
	float			t_max;

	(void)v;
	n = subtract_3dpoints(p , sphere->center);
	n = scale_vector(n, 1 / length(n));
    ratio = 0.0;
	light = scene->lights;
    while (light)
    {
        if (light->type == AMBIENT_LIGHT)
        	ratio += light->ratio;
        else
        {
            if (light->type == POINT_LIGHT)
			{
				l = subtract_3dpoints(light->pos, p);
				t_max = 1;
			}
            else
			{
				l = light->dir;
				t_max = FLT_MAX;
			}
			closest_hit = closest_intersection(p, l, (t_float_range){0.001, t_max}, scene);
			if (!closest_hit.sphere)
			{
				n_dot_l = dot(n, l);
				if (n_dot_l > 0) 
					ratio += light->ratio * n_dot_l / length(l);
				
				// r = subtract_3dvectors(scale_vector(n, 2 * dot(n, l)), l);
				// r_dot_v = dot(r, v);
				// if (r_dot_v > 0)
				// 	ratio += light->ratio * pow(r_dot_v / (length(r) * length(v)), sphere->specular);
			}
		}
		light = light->next;
    }
    return (ratio);
}
