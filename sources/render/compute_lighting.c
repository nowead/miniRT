/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:39:48 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/12 20:45:59 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_normal_vector(t_point3 p, t_obj *obj)
{
	t_vec3	n;

	if (obj->type == SPHERE)
		n = unit_vector(subtract_3dpoints(p, obj->data.sphere.center));
	else
		n = obj->data.plane.normal;
	// else
	// 	n = obj->data.cylinder.vector;
	return (n);
}

float	compute_lighting(t_point3 p, t_vec3 v, t_obj *obj, t_scene *scene)
{
	t_light			*light;
	t_closest_hit	closest_hit;
	t_vec3			n;
	t_vec3			l;
	t_vec3			r;
	float			intens;
	float			n_dot_l;
	float			r_dot_v;
	float			t_max;

	n = get_normal_vector(p, obj);
    intens = 0.0;
	light = scene->lights;
    while (light)
    {
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
			closest_hit = closest_intersection((t_ray){p, l}, (t_float_range){0.001, t_max}, scene);
			if (!closest_hit.obj)
			{
				// apply diffuse reflection
				n_dot_l = dot(n, l);
				if (n_dot_l > 0) 
					intens += light->intens * n_dot_l / length(l);
				// apply specular reflection
				r = subtract_3dvectors(scale_vector(n, 2 * dot(n, l)), l);
				r_dot_v = dot(r, v);
				if (r_dot_v > 0)
					intens += light->intens * pow(r_dot_v / (length(r) * length(v)), obj->specular);
			}
		}
		light = light->next;
    }
    return (intens);
}

int apply_lighting(int color, float lighting)
{
    int r;
	int	g;
	int	b;

    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
    r = (int)(r * lighting);
    g = (int)(g * lighting);
    b = (int)(b * lighting);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
    return ((r << 16) | (g << 8) | b);
}
