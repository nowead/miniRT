/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:58:12 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/06 22:06:59 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_scene(t_vars *vars)
{
	int			x;
	int			y;
	t_vector3d	D;
	int			color;

	x = -(vars->img.width / 2);
	while (x < (vars->img.width / 2))
	{
		y = -(vars->img.height / 2);
		while (y < (vars->img.height / 2))
		{
			D = canvas_to_viewport(x, y, &vars->img);
			color = trace_ray(&vars->scene, D, 1, FLT_MAX);
			my_mlx_pixel_put(x, y, color, &vars->img);
			y++;
		}
		x++;
	}
}

t_vector3d	canvas_to_viewport(int x, int y, t_img *img)
{
	return ((t_vector3d){x * (1 / (float)img->width), y * (1 / (float)img->height), 1});
}

int	trace_ray(t_scene *scene, t_vector3d D, float t_min, float t_max)
{
	t_point3d	p;
	t_inter		inter;

	inter = closest_intersection(scene->camera.pos, D, (t_float_range){t_min, t_max}, scene);
    if (!inter.closest_sphere)
        return (BACKGROUND_COLOR);
	p = add_vector_to_point(scene->camera.pos, scale_vector(D, inter.closest_t));
    return (apply_lighting(inter.closest_sphere->color, compute_lighting(p, scale_vector(D, -1), inter.closest_sphere, scene)));
}

t_inter	closest_intersection(t_point3d O, t_vector3d D, t_float_range t_range, t_scene *scene)
{
	float		closest_t;
	t_sphere	*closest_sphere;
	t_ray_hit	hit;
	int			i;

	closest_t = t_range.max;
    closest_sphere = NULL;
	i = 0;
    while (i < scene->num_of_spheres)
    {
        hit = intersect_ray_sphere(O, D, &(scene->spheres)[i]);
        if ((t_range.min < hit.t1 && hit.t1 < t_range.max) && hit.t1 < closest_t)
        {
            closest_t = hit.t1;
            closest_sphere = &scene->spheres[i];
        }
		if ((t_range.min < hit.t2 && hit.t2 < t_range.max) && hit.t2 < closest_t)
        {
            closest_t = hit.t2;
            closest_sphere = &scene->spheres[i];
        }
		i++;
	}
	return ((t_inter){closest_sphere, closest_t});
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
