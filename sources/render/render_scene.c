/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:58:12 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/08 16:38:51 by damin            ###   ########.fr       */
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

int	trace_ray(t_obj *obj, t_vector3d D, float t_min, float t_max)
{
    float		closest_t;
	t_sphere	*closest_sphere;
	int			i;
	t_hit		hit;

	closest_t = t_max;
    closest_sphere = NULL;
	i = 0;
    while (i < obj->num_of_spheres)
    {
        hit = intersect_ray_sphere(obj->camera, D, &(obj->spheres)[i]);
        if ((t_min < hit.t1 && hit.t1 < t_max) && hit.t1 < closest_t) 
        {
            closest_t = hit.t1;
            closest_sphere = &obj->spheres[i];
        }
		if ((t_min < hit.t2 && hit.t2 < t_max) && hit.t2 < closest_t) 
        {
            closest_t = hit.t2;
            closest_sphere = &obj->spheres[i];
        }
		i++;
	}
    if (closest_sphere == NULL) 
        return (BACKGROUND_COLOR);
    return (closest_sphere->color);
}

t_hit	intersect_ray_sphere(t_point3d O, t_vector3d D, \
t_sphere *sphere)
{
	float		r;
	float		t1;
	float		t2;
	float		discriminant;
	t_vector3d	CO;
	float		a;
	float		b;
	float		c;
	
	
    r = sphere->radius;
    CO = subtract_3dpoints(O, sphere->center);
    a = dot(D, D);
    b = 2 * dot(CO, D);
    c = dot(CO, CO) - (r * r);

    discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return ((t_hit){FLT_MAX, FLT_MAX});

    t1 = (-b + sqrt(discriminant)) / (2 * a);
    t2 = (-b - sqrt(discriminant)) / (2 * a);
    
    return ((t_hit){t1, t2});
}

t_vector3d	subtract_3dpoints(t_point3d p1, t_point3d p2)
{
	return ((t_vector3d){p1.x - p2.x, p1.y - p2.y, p1.z - p2.z});
}

float	dot(t_vector3d v1, t_vector3d v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}
