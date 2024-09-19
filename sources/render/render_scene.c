/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:58:12 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/19 20:50:18 by damin            ###   ########.fr       */
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

t_vec3 world_to_local(t_vec3 p, t_vec3 cylinder_axis, t_point3 cylinder_center)
{
	t_vec3	local_op;
	t_vec3	dir;
	t_vec3	op;
	t_vec3	op_perp;
	t_vec3	arbitrary_vector;

	dir = unit_vector(cylinder_axis);
	op = subtract_3dpoints(p, cylinder_center);
	local_op.y = dot(op, dir);
	op_perp = subtract_3dpoints(op, scale_vector(dir, local_op.y));
	arbitrary_vector = (t_vec3){1, 0, 0};
	if (fabs(dot(dir, arbitrary_vector)) > 0.99)
		arbitrary_vector = (t_vec3){0, 1, 0};
	local_op.x = dot(op_perp,unit_vector(cross(dir, arbitrary_vector)));
	local_op.z = dot(op_perp, cross(dir, unit_vector(cross(dir, arbitrary_vector))));
	return (local_op);
}

void	p_to_uv(t_point3 p, t_obj *obj, t_sub_obj sub_obj)
{
	t_vec3	op;

	if (obj->type == SPHERE)
	{
		op = subtract_3dpoints(p, obj->data.sphere.center);
		obj->checkerboard.u = 0.5 - atan2(op.x, op.z) / (2 * M_PI);
		obj->checkerboard.v = 1 - acos(op.y / obj->data.sphere.radius) / M_PI;
	}
	else if (obj->type == PLANE)
	{
		op = subtract_3dpoints(p, obj->data.plane.pos);
		obj->checkerboard.u = fmod(op.x, 1);
		obj->checkerboard.v = fmod(op.z, 1);
	}
	else if (obj->type == CYLINDER)
	{
		op = world_to_local(p, obj->data.cylinder.side.axis, obj->data.cylinder.side.center);
		obj->checkerboard.u = 0.5 - atan2(op.x, op.z) / (2 * M_PI);
		obj->checkerboard.v = fmod(op.y, 1);
		if (sub_obj == TOP_CAP || sub_obj == BOTTOM_CAP)
		{
			obj->checkerboard.u = 0.5 - atan2(op.x, op.z) / (2 * M_PI); // U 좌표 (각도)
			obj->checkerboard.v = sqrt(op.x * op.x + op.z * op.z); // V 좌표 (반지름에 따라)
		}
	}
	else if (obj->type == CONE)
	{
		op = world_to_local(p, obj->data.cone.side.axis, obj->data.cone.side.vertex);
		obj->checkerboard.u = 0.5 - atan2(op.x, op.z) / (2 * M_PI);
		obj->checkerboard.v = fmod(-op.y, 1);
		if (sub_obj == BOTTOM_CAP)
		{
			obj->checkerboard.u = 0.5 - atan2(op.x, op.z) / (2 * M_PI); // U 좌표 (각도)
			obj->checkerboard.v = sqrt(op.x * op.x + op.z * op.z); // V 좌표 (반지름에 따라)
		}
	}
}

int	uv_mapping(t_obj *obj)
{
	int		u;
	int		v;
	int		checkerboard_color;

	u = floor(obj->checkerboard.u * obj->checkerboard.width);
	v = floor(obj->checkerboard.v * obj->checkerboard.height);
	if ((u + v) % 2 == 0)
		checkerboard_color = obj->checkerboard.color1;
	else
		checkerboard_color = obj->checkerboard.color2;
	return (checkerboard_color);
}

t_color	get_p_color(t_point3 p, t_closest_hit *closest_hit)
{
	if (!closest_hit->obj->checkerboard.checkerboard_on)
		return (closest_hit->obj->color);
	p_to_uv(p, closest_hit->obj, closest_hit->sub_obj);
	return (int_to_t_color(uv_mapping(closest_hit->obj)));
}

t_color int_to_t_color(int int_color)
{
	t_color color;

	color.r = (int_color >> 16) & 0xFF;
	color.g = (int_color >> 8) & 0xFF;
	color.b = int_color & 0xFF;
	return (color);
}

int	trace_ray(t_scene *scene, t_vec3 ray_dir)
{
	t_point3		p;
	t_closest_hit	closest_hit;
	t_color			lighting;

	closest_hit = closest_intersection((t_ray){scene->camera.pos, ray_dir}, \
	(t_float_range){0, FLT_MAX}, scene);
    if (!closest_hit.obj)
        return (BACKGROUND_COLOR);
	p = add_vector_to_point(scene->camera.pos, \
	scale_vector(ray_dir, closest_hit.t));
	lighting = compute_lighting(p, scale_vector(ray_dir, -1), &closest_hit, scene);
    return (apply_lighting(get_p_color(p, &closest_hit), &lighting));
}
