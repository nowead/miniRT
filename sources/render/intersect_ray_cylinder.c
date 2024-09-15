/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_ray_cylinder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:26:26 by damin             #+#    #+#             */
/*   Updated: 2024/09/15 17:28:02 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void intersect_ray_cylinder(t_ray *ray, t_obj *obj, t_float_range t_range, t_closest_hit *closest_hit)
{
    t_cylinder_vars vars;
    float   t1;
    float   t2;
    t_vec3  bottom_center;
    t_vec3  top_center;

    vars = (t_cylinder_vars){0};
    get_cylinder_vars(ray, obj, &vars);
    if (solve_quadratic(&vars, &t1, &t2))
    {
        check_side_hit(t1, &vars, t_range, closest_hit, obj);
        check_side_hit(t2, &vars, t_range, closest_hit, obj);
    }
    bottom_center = obj->data.cylinder.center;
    check_cap_intersection(ray, &vars, bottom_center, -1, t_range, closest_hit, obj);
    top_center = add_vector_to_point(obj->data.cylinder.center, scale_vector(vars.V, vars.h));
    check_cap_intersection(ray, &vars, top_center, 1, t_range, closest_hit, obj);
}

void get_cylinder_vars(t_ray *ray, t_obj *obj, t_cylinder_vars *vars)
{
    vars->D = ray->dir;
    vars->V = obj->data.cylinder.axis; // Should be a unit vector
    vars->CO = subtract_3dpoints(ray->origin, obj->data.cylinder.center);
    vars->r = obj->data.cylinder.radius;
    vars->h = obj->data.cylinder.height;
    vars->D_dot_V = dot(vars->D, vars->V);
    vars->CO_dot_V = dot(vars->CO, vars->V);
    vars->D_perp = subtract_3dvectors(vars->D, scale_vector(vars->V, vars->D_dot_V));
    vars->CO_perp = subtract_3dvectors(vars->CO, scale_vector(vars->V, vars->CO_dot_V));
    vars->a = dot(vars->D_perp, vars->D_perp);
    vars->b = 2 * dot(vars->D_perp, vars->CO_perp);
    vars->c = dot(vars->CO_perp, vars->CO_perp) - (vars->r * vars->r);
}

int solve_quadratic(t_cylinder_vars *vars, float *t1, float *t2)
{
    float discriminant;
    float sqrt_discriminant;

    discriminant = vars->b * vars->b - 4 * vars->a * vars->c;
    if (discriminant < 0)
        return 0;
    sqrt_discriminant = sqrt(discriminant);
    *t1 = (-vars->b - sqrt_discriminant) / (2 * vars->a);
    *t2 = (-vars->b + sqrt_discriminant) / (2 * vars->a);
    return 1;
}

void check_side_hit(float t, t_cylinder_vars *vars, t_float_range t_range, t_closest_hit *closest_hit, t_obj *obj)
{
    float m;

    if (t_range.min < t && t < t_range.max)
    {
        m = vars->D_dot_V * t + vars->CO_dot_V;
        if (0 <= m && m <= vars->h)
        {
            if (t < closest_hit->t)
            {
                closest_hit->t = t;
                closest_hit->obj = obj;
                closest_hit->sub_obj = SIDE;
            }
        }
    }
}

void check_cap_intersection(t_ray *ray, t_cylinder_vars *vars, t_vec3 cap_center, int cap_orientation, t_float_range t_range, t_closest_hit *closest_hit, t_obj *obj)
{
    float denom;
    float t;
    t_vec3 P;
    t_vec3 v;
    float dist;

    denom = dot(ray->dir, vars->V);
    if (fabs(denom) > 1e-6)
    {
        t = dot(vars->V, subtract_3dpoints(cap_center, ray->origin)) / denom;
        if (t_range.min < t && t < t_range.max && t < closest_hit->t)
        {
            P = add_vector_to_point(ray->origin, scale_vector(ray->dir, t));
            v = subtract_3dpoints(P, cap_center);
            dist = length(subtract_3dvectors(v, scale_vector(vars->V, dot(v, vars->V))));
            if (dist <= vars->r)
            {
                closest_hit->t = t;
                closest_hit->obj = obj;
				if (cap_orientation == 1)
                	closest_hit->sub_obj = TOP_CAP;
				else
					closest_hit->sub_obj = BOTTOM_CAP;
            }
        }
    }
}
