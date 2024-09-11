/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:58:12 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/10 21:29:15 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_scene(t_vars *vars)
{
	int			x;
	int			y;
	t_vec3		ray_dir;
	int			color;

	x = -(vars->img.width / 2);
	while (x < (vars->img.width / 2))
	{
		y = -(vars->img.height / 2);
		while (y < (vars->img.height / 2))
		{
			ray_dir = rotate_camera(vars->scene.camera.dir, canvas_to_viewport(x, y, &vars->img, vars->scene.camera.fov));
			color = trace_ray(&vars->scene, ray_dir);
			my_mlx_pixel_put(x, y, color, &vars->img);
			y++;
		}
		x++;
	}
}

t_vec3	canvas_to_viewport(int x, int y, t_img *img, int fov)
{
	float	viewport_w;
	float	viewport_h;
	float	fov_radian;

	fov_radian = fov * M_PI / 180;
	viewport_w = 2 * tan((float)fov_radian / 2);
	viewport_h = viewport_w * (img->height / (float)img->width);
	return ((t_vec3){x * (viewport_w / (float)img->width), y * (viewport_h / (float)img->height), 1});
}

t_vec3	rotate_camera(t_vec3 camera_dir, t_vec3 d)
{
	t_vec3	rotation_axis;
	float	cosine_angle;
	float	angle;
	t_vec3	rotated_vector;
	t_vec3	term1;
	t_vec3	term2;
	t_vec3	term3;

	cosine_angle = cosine_between_vectors(camera_dir, (t_vec3){0, 0, 1});
	if (cosine_angle == 1)
		return (d);
	if (cosine_angle == -1)
		return (scale_vector(d, -1));
	rotation_axis = unit_vector(cross(camera_dir, (t_vec3){0, 0, 1}));
	angle = acos(cosine_angle);
	// Rodrigues' rotation formula
	term1 = scale_vector(d, cos(angle));
	term2 = scale_vector(cross(rotation_axis, d), sin(angle));
	term3 = scale_vector(rotation_axis, dot(rotation_axis, d) * (1 - cos(angle)));
	rotated_vector = add_3dvectors(add_3dvectors(term1, term2), term3);
	return (rotated_vector);
}

int	trace_ray(t_scene *scene, t_vec3 ray_dir)
{
	t_point3		p;
	t_closest_hit	closest_hit;

	closest_hit = closest_intersection((t_ray){scene->camera.pos, ray_dir}, (t_float_range){0, FLT_MAX}, scene);
    if (!closest_hit.obj)
        return (BACKGROUND_COLOR);
	p = add_vector_to_point(scene->camera.pos, scale_vector(ray_dir, closest_hit.t));
    return (apply_lighting(closest_hit.obj->color, compute_lighting(p, scale_vector(ray_dir, -1), closest_hit.obj, scene)));
}

t_closest_hit	closest_intersection(t_ray ray, t_float_range t_range, t_scene *scene)
{
	t_closest_hit	closest_hit;
	t_obj			*obj;

	closest_hit.t = t_range.max;
    closest_hit.obj = NULL;
	obj = scene->obj;
    while (obj)
    {
		if (obj->type == SPHERE)
        	intersect_ray_sphere(&ray, obj, t_range, &closest_hit);
		else if (obj->type == PLANE)
			intersect_ray_plane(&ray, obj, t_range, &closest_hit);
		// else if (scene->obj[i].type == CYLINDER)
		// 	closest_hit = intersect_ray_plane(scene->camera, ray_dir, &(scene->obj[i]), &closest_hit);
		obj = obj->next;
	}
	return (closest_hit);
}
