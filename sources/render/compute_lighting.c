/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:39:48 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/25 14:29:30 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define N 0
#define L 1
#define R 2
#define V 3

t_color	compute_lighting(t_point3 p, t_vec3 v, t_closest_hit *hit, \
t_scene *scene)
{
	t_light			*light;
	t_closest_hit	closest_hit;
	t_vec3			vec[4];
	t_color			intens;

	vec[N] = get_normal_vector(p, hit);
	vec[V] = v;
	intens = (t_color){0, 0, 0};
	light = scene->lights;
	while (light)
	{
		if (light->type == AMBIENT_LIGHT)
			add_light_intensity(&intens, light->intens, &light->color_intens);
		else
		{
			if (light->type == POINT_LIGHT)
				vec[L] = subtract_3dpoints(light->pos, p);
			closest_hit = closest_intersection((t_ray){p, vec[L]}, \
			(t_float_range){0.001, 1}, scene);
			if (!closest_hit.obj)
				apply_diffuse_and_specular_lighting(hit, light, &intens, vec);
		}
		light = light->next;
	}
	return (clamp_light_intens(intens));
}

void	apply_diffuse_and_specular_lighting(t_closest_hit *hit, \
t_light *light, t_color *intens, t_vec3 vec[3])
{
	float	n_dot_l;
	float	r_dot_v;
	float	factor;

	n_dot_l = dot(vec[N], vec[L]);
	if (n_dot_l > 0)
	{
		factor = light->intens * n_dot_l / length(vec[L]);
		add_light_intensity(intens, factor, &light->color_intens);
	}
	if (hit->obj->specular > 0)
	{
		vec[R] = subtract_vectors(scale_vector(vec[N], \
		2 * dot(vec[N], vec[L])), vec[L]);
		r_dot_v = dot(vec[R], vec[V]);
		if (r_dot_v > 0)
		{
			factor = light->intens * pow(r_dot_v / \
			(length(vec[R]) * length(vec[V])), hit->obj->specular);
			add_light_intensity(intens, factor, \
			&light->color_intens);
		}
	}
}

t_color	clamp_light_intens(t_color intens)
{
	intens.r = fminf(intens.r, 1.0f);
	intens.g = fminf(intens.g, 1.0f);
	intens.b = fminf(intens.b, 1.0f);
	return (intens);
}

void	add_light_intensity(t_color *intens, float factor, \
t_color *color_intens)
{
	intens->r += factor * color_intens->r;
	intens->g += factor * color_intens->g;
	intens->b += factor * color_intens->b;
}

int	apply_lighting(t_color color, t_color *lighting)
{
	int	r;
	int	g;
	int	b;

	r = (int)(color.r * lighting->r);
	g = (int)(color.g * lighting->g);
	b = (int)(color.b * lighting->b);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}
