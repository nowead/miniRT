/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_ray_cylinder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:26:26 by damin             #+#    #+#             */
/*   Updated: 2024/09/13 18:39:15 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void get_cylinder_vars(t_ray *ray, t_obj *obj, t_cylinder_vars *vars)
{
    vars->D = ray->dir;
    vars->V = obj->data.cylinder.vector; // Should be a unit vector
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
                closest_hit->is_cap = 0; // Side hit
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
                closest_hit->is_cap = 1; // Cap hit
                closest_hit->cap_normal = cap_orientation == 1 ? vars->V : scale_vector(vars->V, -1);
            }
        }
    }
}

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

// void intersect_ray_cylinder(t_ray *ray, t_obj *obj, t_float_range t_range, \
//     t_closest_hit *closest_hit)
// {
//     float   a;
//     float   b;
//     float   c;
//     float   discriminant;
//     float   t1;
//     float   t2;
//     float   sqrt_discriminant;
//     t_vec3  CO;
//     t_vec3  D;
//     t_vec3  V;
//     float   D_dot_V;
//     t_vec3  D_perp;
//     float   CO_dot_V;
//     t_vec3  CO_perp;
//     float   m1;
//     float   m2;
//     float   r;
//     float   h;
    
//     D = ray->dir;
//     V = obj->data.cylinder.vector; // 원기둥의 축 방향 벡터 (단위 벡터여야 함)
//     CO = subtract_3dpoints(ray->origin, obj->data.cylinder.center);
//     r = obj->data.cylinder.radius;
//     h = obj->data.cylinder.height;
    
//     D_dot_V = dot(D, V);
//     CO_dot_V = dot(CO, V);
    
//     D_perp = subtract_3dvectors(D, scale_vector(V, D_dot_V));
//     CO_perp = subtract_3dvectors(CO, scale_vector(V, CO_dot_V));
    
//     a = dot(D_perp, D_perp);
//     b = 2 * dot(D_perp, CO_perp);
//     c = dot(CO_perp, CO_perp) - (r * r);
    
//     discriminant = b * b - 4 * a * c;
    
//     if (discriminant >= 0)
//     {
//         sqrt_discriminant = sqrt(discriminant);
    
//         t1 = (-b - sqrt_discriminant) / (2 * a);
//         t2 = (-b + sqrt_discriminant) / (2 * a);
    
//         // t1 검사
//         if (t_range.min < t1 && t1 < t_range.max)
//         {
//             m1 = D_dot_V * t1 + CO_dot_V;
//             if (0 <= m1 && m1 <= h)
//             {
//                 if (t1 < closest_hit->t)
//                 {
//                     closest_hit->t = t1;
//                     closest_hit->obj = obj;
//                     closest_hit->is_cap = 0; // 측면 히트
//                 }
//             }
//         }
    
//         // t2 검사
//         if (t_range.min < t2 && t2 < t_range.max)
//         {
//             m2 = D_dot_V * t2 + CO_dot_V;
//             if (0 <= m2 && m2 <= h)
//             {
//                 if (t2 < closest_hit->t)
//                 {
//                     closest_hit->t = t2;
//                     closest_hit->obj = obj;
//                     closest_hit->is_cap = 0; // 측면 히트
//                 }
//             }
//         }
//     }
    
//     // 아랫면(밑면) 검사
//     {
//         float t;
//         float denom = dot(D, V);
//         if (fabs(denom) > 1e-6)
//         {
//             t = - (dot(CO, V)) / denom;
//             if (t_range.min < t && t < t_range.max && t < closest_hit->t)
//             {
//                 t_vec3 P = add_vector_to_point(ray->origin, scale_vector(D, t));
//                 t_vec3 v = subtract_3dpoints(P, obj->data.cylinder.center);
//                 float dist = length(subtract_3dvectors(v, scale_vector(V, dot(v, V))));
//                 if (dist <= r)
//                 {
//                     closest_hit->t = t;
//                     closest_hit->obj = obj;
//                     closest_hit->is_cap = 1; // 캡 히트
//                     closest_hit->cap_normal = scale_vector(V, -1); // 밑면의 법선은 -V
//                 }
//             }
//         }
//     }
    
//     // 윗면 검사
//     {
//         float t;
//         float denom = dot(D, V);
//         if (fabs(denom) > 1e-6)
//         {
//             t_vec3 top_center = add_vector_to_point(obj->data.cylinder.center, scale_vector(V, h));
//             t = (dot(V, subtract_3dpoints(top_center, ray->origin))) / denom;
//             if (t_range.min < t && t < t_range.max && t < closest_hit->t)
//             {
//                 t_vec3 P = add_vector_to_point(ray->origin, scale_vector(D, t));
//                 t_vec3 v = subtract_3dpoints(P, top_center);
//                 float dist = length(subtract_3dvectors(v, scale_vector(V, dot(v, V))));
//                 if (dist <= r)
//                 {
//                     closest_hit->t = t;
//                     closest_hit->obj = obj;
//                     closest_hit->is_cap = 1; // 캡 히트
//                     closest_hit->cap_normal = V; // 윗면의 법선은 V
//                 }
//             }
//         }
//     }
    
//     return ;
// }