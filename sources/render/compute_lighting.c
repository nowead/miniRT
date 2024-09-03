/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:39:48 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/03 21:57:58 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	compute_lighting(t_point3d p, t_vector3d n, t_scene *scene)
{
	t_light		*light;
	t_vector3d	l;
	float		intens;
	float		n_dot_l;
	int			i;

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
		}
		i++;
    }
	if (intens > 1.0)
		intens = 1.0;
	if (intens < 0.0)
		intens = 0.0;
    return (intens);
}
