/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_ray_cylinder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:26:26 by damin             #+#    #+#             */
/*   Updated: 2024/09/23 16:53:22 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define CO_DOT_AXIS 0
#define D_DOT_AXIS 1

void intersect_ray_cylinder(t_inter_vars vars)
{
	intersect_ray_cylinder_side(&vars);
	intersect_ray_cylinder_cap(&vars, TOP_CAP);
	intersect_ray_cylinder_cap(&vars, BOTTOM_CAP);
}

void	intersect_ray_cylinder_side(t_inter_vars *vars)
{
	t_cy_side	*cylinder;
	t_vec3		co;
	float		term[2];
	float		coeff[3];
    float		t[2];

	cylinder = &vars->obj->data.cylinder.side;
	co = subtract_3dpoints(vars->ray->origin, cylinder->center);
    term[CO_DOT_AXIS] = dot(co, cylinder->axis);
    term[D_DOT_AXIS] = dot(vars->ray->dir, cylinder->axis);
	compute_cylinder_side_quadratic_coefficients(vars, coeff, &co, term);
    if (solve_quadratic_equation(coeff, t))
    {
		if (is_p_within_cylinder_height(term[CO_DOT_AXIS], term[D_DOT_AXIS], t[0], cylinder->height))
			update_closest_hit(t[0], SIDE, vars);
		if (is_p_within_cylinder_height(term[CO_DOT_AXIS], term[D_DOT_AXIS], t[1], cylinder->height))
			update_closest_hit(t[1], SIDE, vars);
    }
}

void compute_cylinder_side_quadratic_coefficients(t_inter_vars *vars, float coeff[3], t_vec3 *co, float term[2])
{
	t_cy_side	*cylinder;
	t_vec3		d_perp;
	t_vec3		co_perp;

	cylinder = &vars->obj->data.cylinder.side;
    d_perp = subtract_vectors(vars->ray->dir, scale_vector(cylinder->axis, term[D_DOT_AXIS]));
    co_perp = subtract_vectors(*co, scale_vector(cylinder->axis, term[CO_DOT_AXIS]));
    coeff[0] = dot(d_perp, d_perp);
    coeff[1] = 2 * dot(d_perp, co_perp);
    coeff[2] = dot(co_perp, co_perp) - (cylinder->radius * cylinder->radius);
}

int	is_p_within_cylinder_height(float co_dot_axis, float d_dot_axis, float t, float h)
{
    float m;

	m = d_dot_axis * t + co_dot_axis;
	if (0 <= m && m <= h)
		return (1);
	return (0);
}

void	intersect_ray_cylinder_cap(t_inter_vars *vars, t_sub_obj sub_obj)
{
	float		t;
	t_circle	*cap;

	if (sub_obj == TOP_CAP)
		cap = &vars->obj->data.cylinder.top_cap;
	else
		cap = &vars->obj->data.cylinder.bottom_cap;
	if (compute_circle_intersection(vars->ray, cap, &t))
		update_closest_hit(t, sub_obj, vars);
}
