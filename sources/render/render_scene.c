/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:58:12 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/12 20:42:56 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_scene(t_vars *vars)
{
	int			x;
	int			y;
	t_vec3		ray_dir;
	int			color;

	init_camera_and_viewport(&vars->scene.camera, &vars->img);
	x = -(vars->img.width / 2);
	while (x < (vars->img.width / 2))
	{
		y = -(vars->img.height / 2);
		while (y < (vars->img.height / 2))
		{
			ray_dir = canvas_to_viewport(x, y, &vars->img, &vars->scene.camera);
			color = trace_ray(&vars->scene, ray_dir);
			my_mlx_pixel_put(x, y, color, &vars->img);
			y++;
		}
		x++;
	}
}

void	init_camera_and_viewport(t_camera *camera, t_img *img)
{
	t_vec3	w;

	camera->fov_radian = camera->fov * M_PI / 180;
	camera->viewport_w = 2 * tan((float)camera->fov_radian / 2);
	camera->viewport_h = camera->viewport_w * (img->height / (float)img->width);
	camera->viewport_c = add_vector_to_point(camera->pos, unit_vector(camera->dir));
	w = unit_vector(camera->dir);
	camera->u = unit_vector(cross((t_vec3){0,1,0}, w));
	camera->v = cross(w, camera->u);
}

t_vec3	canvas_to_viewport(int x, int y, t_img *img, t_camera *camera)
{
	float		x_offset;
	float		y_offset;
	t_vec3		x_component;
	t_vec3		y_component;
	t_point3	p;

	x_offset = x * (camera->viewport_w / (float)img->width);
	y_offset = y * (camera->viewport_h / (float)img->height);
	x_component = scale_vector(camera->u, x_offset);
	y_component = scale_vector(camera->v, y_offset);
	p = add_vector_to_point(add_vector_to_point(camera->viewport_c, x_component), y_component);
	return (subtract_3dpoints(p, camera->pos));
}

int	trace_ray(t_scene *scene, t_vec3 ray_dir)
{
	t_point3		p;
	t_closest_hit	closest_hit;

	closest_hit = closest_intersection((t_ray){scene->camera.pos, ray_dir}, \
	(t_float_range){0, FLT_MAX}, scene);
    if (!closest_hit.obj)
        return (BACKGROUND_COLOR);
	p = add_vector_to_point(scene->camera.pos, \
	scale_vector(ray_dir, closest_hit.t));
    return (apply_lighting(closest_hit.obj->color, \
	compute_lighting(p, scale_vector(ray_dir, -1), closest_hit.obj, scene)));
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
		// else if (obj->type == CONE)
		// 	intersect_ray_cone(&ray, obj, t_range, &closest_hit);
		obj = obj->next;
	}
	return (closest_hit);
}
