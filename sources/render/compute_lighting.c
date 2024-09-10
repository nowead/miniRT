/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:39:48 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/08 17:06:51 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	compute_lighting(t_point3d p, t_vector3d v, t_sphere *sphere, t_scene *scene)
{
	t_light			*light;
	t_closest_hit	closest_hit;
	t_vector3d		n;
	t_vector3d		l;
	t_vector3d		r;
	float			intens;
	float			n_dot_l;
	float			r_dot_v;
	int				i;
	float			t_max;

	n = subtract_3dpoints(p , sphere->center);
	n = scale_vector(n, 1 / length(n));
    intens = 0.0;
	i = 0;
    while (i < scene->num_of_lights)
    {
		light = &(scene->lights[i]);
        if (light->type == AMBIENT_LIGHT)
        	intens += light->intens;
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
					intens += light->intens * n_dot_l / length(l);
				
				r = subtract_3dvectors(scale_vector(n, 2 * dot(n, l)), l);
				r_dot_v = dot(r, v);
				if (r_dot_v > 0)
					intens += light->intens * pow(r_dot_v / (length(r) * length(v)), sphere->specular);
			}
		}
		i++;
    }
    return (intens);
}
