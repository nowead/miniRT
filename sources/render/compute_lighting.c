/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:39:48 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/14 14:13:58 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
t_vec3 get_cylinder_normal(t_point3 p, t_closest_hit *hit)
{
	t_vec3	temp;
	t_vec3	q;
	float	m;

	if (hit->sub_obj == TOP_CAP)
		return (hit->obj->data.cylinder.vector);
	else if (hit->sub_obj == BOTTOM_CAP)
		return (scale_vector(hit->obj->data.cylinder.vector, -1));
	else
	{
		temp = subtract_3dpoints(p, hit->obj->data.cylinder.center);
        m = dot(temp, hit->obj->data.cylinder.vector);
        q = add_vector_to_point(hit->obj->data.cylinder.center,\
		 scale_vector(hit->obj->data.cylinder.vector, m));
        return (unit_vector(subtract_3dpoints(p, q)));
	}
}

t_vec3	get_normal_vector(t_point3 p, t_closest_hit *hit)
{
	t_vec3	n;

	if (hit->obj->type == SPHERE)
		n = unit_vector(subtract_3dpoints(p, hit->obj->data.sphere.center));
	else if (hit->obj->type == PLANE)
		n = hit->obj->data.plane.normal;
	else
		n = get_cylinder_normal(p, hit);
	return (n);
}

float	compute_lighting(t_point3 p, t_vec3 v, t_closest_hit *hit, t_scene *scene)
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

	n = get_normal_vector(p, hit);
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
					intens += light->intens * pow(r_dot_v / (length(r) * length(v)), hit->obj->specular);
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
