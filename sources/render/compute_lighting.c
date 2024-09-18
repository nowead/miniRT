/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:39:48 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/18 18:15:11 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	compute_lighting(t_point3 p, t_vec3 v, t_closest_hit *hit, t_scene *scene)
{
	t_light			*light;
	t_closest_hit	closest_hit;
	t_vec3			n;
	t_vec3			l;
	t_vec3			r;
	t_color			intens;
	float			factor;
	float			n_dot_l;
	float			r_dot_v;
	float			t_max;

	n = get_normal_vector(p, hit);
    intens = (t_color){0.0, 0.0, 0.0};
	light = scene->lights;
    while (light)
    {
        if (light->type == AMBIENT_LIGHT)
        	add_light_intensity(&intens, light->intens, &light->color_intens);
        else
        {
            if (light->type == POINT_LIGHT)
			{
				l = subtract_3dpoints(light->pos, p);
				t_max = 1;
			}
			closest_hit = closest_intersection((t_ray){p, l}, (t_float_range){0.001, t_max}, scene);
			if (!closest_hit.obj)
			{
				// apply diffuse reflection
				n_dot_l = dot(n, l);
				if (n_dot_l > 0)
				{		
					factor = light->intens * n_dot_l / length(l);
					add_light_intensity(&intens, factor, &light->color_intens);
				}
				// apply specular reflection
				if (hit->obj->specular > 0)
				{
					r = subtract_3dvectors(scale_vector(n, 2 * dot(n, l)), l);
					r_dot_v = dot(r, v);
					if (r_dot_v > 0)
					{
						factor = light->intens * pow(r_dot_v / (length(r) * length(v)), hit->obj->specular);
						add_light_intensity(&intens, factor, &light->color_intens);
					}
				}
			}
		}
		light = light->next;
    }
	intens.r = fminf(intens.r, 1.0f);
	intens.g = fminf(intens.g, 1.0f);
	intens.b = fminf(intens.b, 1.0f);
    return (intens);
}

void	add_light_intensity(t_color *intens, float factor, t_color *color_intens)
{
	intens->r += factor * color_intens->r;
	intens->g += factor * color_intens->g;
	intens->b += factor * color_intens->b;
}

int apply_lighting(t_color *color, t_color *lighting)
{
    int r;
	int	g;
	int	b;

	r = (int)(color->r * lighting->r);
	g = (int)(color->g * lighting->g);
	b = (int)(color->b * lighting->b);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}
