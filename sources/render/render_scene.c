/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:58:12 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/10 18:59:50 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_scene(t_vars *vars)
{
	int			x;
	int			y;
	t_vector3d	ray_dir;
	int			color;

	x = -(vars->img.width / 2);
	while (x < (vars->img.width / 2))
	{
		y = -(vars->img.height / 2);
		while (y < (vars->img.height / 2))
		{
			ray_dir = rotate_camera(vars->scene.camera.dir, canvas_to_viewport(x, y, &vars->img, vars->scene.camera.fov));
			color = trace_ray(&vars->scene, ray_dir, 0, FLT_MAX);
			my_mlx_pixel_put(x, y, color, &vars->img);
			y++;
		}
		x++;
	}
}

t_vector3d	canvas_to_viewport(int x, int y, t_img *img, int fov)
{
	float	viewport_w;
	float	viewport_h;
	float	fov_radian;

	fov_radian = fov * M_PI / 180;
	viewport_w = 2 * tan((float)fov_radian / 2);
	viewport_h = viewport_w * (img->height / (float)img->width);
	return ((t_vector3d){x * (viewport_w / (float)img->width), y * (viewport_h / (float)img->height), 1});
}

t_vector3d	rotate_camera(t_vector3d camera_dir, t_vector3d d)
{
	t_vector3d	rotation_axis;
	float		cosine_angle;
	float		angle;
	t_vector3d	rotated_vector;
	t_vector3d	term1;
	t_vector3d	term2;
	t_vector3d	term3;

	cosine_angle = cosine_between_vectors(camera_dir, (t_vector3d){0, 0, 1});
	if (cosine_angle == 1)
		return (d);
	if (cosine_angle == -1)
		return (scale_vector(d, -1));
	rotation_axis = normalize_vector(cross(camera_dir, (t_vector3d){0, 0, 1}));
	angle = acos(cosine_angle);
	// Rodrigues' rotation formula
	term1 = scale_vector(d, cos(angle));
	term2 = scale_vector(cross(rotation_axis, d), sin(angle));
	term3 = scale_vector(rotation_axis, dot(rotation_axis, d) * (1 - cos(angle)));
	rotated_vector = add_3dvectors(add_3dvectors(term1, term2), term3);
	return (rotated_vector);
}

int	trace_ray(t_scene *scene, t_vector3d ray_dir, float t_min, float t_max)
{
	t_point3d		p;
	t_closest_hit	closest_hit;

	closest_hit = closest_intersection(scene->camera.pos, ray_dir, (t_float_range){t_min, t_max}, scene);
    if (!closest_hit.sphere)
        return (BACKGROUND_COLOR);
	p = add_vector_to_point(scene->camera.pos, scale_vector(ray_dir, closest_hit.t));
    return (apply_lighting(closest_hit.sphere->color, compute_lighting(p, scale_vector(ray_dir, -1), closest_hit.sphere, scene)));
}

t_closest_hit	closest_intersection(t_point3d O, t_vector3d D, t_float_range t_range, t_scene *scene)
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
	return ((t_closest_hit){closest_sphere, closest_t});
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
