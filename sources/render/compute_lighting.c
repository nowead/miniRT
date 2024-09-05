/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:39:48 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/05 21:38:30 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	compute_lighting(t_point3d p, t_vector3d v, t_sphere *sphere, t_scene *scene)
{
	t_light		*light;
	t_vector3d	n;
	t_vector3d	l;
	t_vector3d	r;
	float		intens;
	float		n_dot_l;
	float		r_dot_v;
	int			i;

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
                l = subtract_3dpoints(light->pos, p);
            else
                l = light->dir;
			n_dot_l = dot(n, l);
			if (n_dot_l > 0) 
				intens += light->intens * n_dot_l / length(l);
			
			r = subtract_3dvectors(scale_vector(n, 2 * dot(n, l)), l);
			r_dot_v = dot(r, v);
			if (r_dot_v > 0)
				intens += light->intens * pow(r_dot_v / (length(r) * length(v)), sphere->specular);
		}
		i++;
    }
	if (intens > 1.0)
		intens = 1.0;
    return (intens);
}
