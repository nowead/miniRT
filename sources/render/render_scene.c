/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:58:12 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/03 22:04:19 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int apply_lighting(int color, float lighting);

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
    float		closest_t;
	t_sphere	*closest_sphere;
	int			i;
	t_ray_hit	hit;
	t_point3d	p;
	t_vector3d	n;

	closest_t = t_max;
    closest_sphere = NULL;
	i = 0;
    while (i < scene->num_of_spheres)
    {
        hit = intersect_ray_sphere(scene->camera.pos, D, &(scene->spheres)[i]);
        if ((t_min < hit.t1 && hit.t1 < t_max) && hit.t1 < closest_t)
        {
            closest_t = hit.t1;
            closest_sphere = &scene->spheres[i];
        }
		if ((t_min < hit.t2 && hit.t2 < t_max) && hit.t2 < closest_t)
        {
            closest_t = hit.t2;
            closest_sphere = &scene->spheres[i];
        }
		i++;
	}
    if (closest_sphere == NULL)
        return (BACKGROUND_COLOR);
	p = add_vector_to_point(scene->camera.pos, scale_vector(D, closest_t));
	n = subtract_3dpoints(p , closest_sphere->center);
	n = scale_vector(n, 1 / length(n));
    return (apply_lighting(closest_sphere->color, compute_lighting(p, n, scene)));
}

int apply_lighting(int color, float lighting)
{
    int r, g, b;

    // Extract RGB components
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;

    // Apply lighting
    r = (int)(r * lighting);
    g = (int)(g * lighting);
    b = (int)(b * lighting);

    // Clamp the values to the [0, 255] range
    r = r > 255 ? 255 : r;
    g = g > 255 ? 255 : g;
    b = b > 255 ? 255 : b;

    // Reassemble the color
    return (r << 16) | (g << 8) | b;
}
