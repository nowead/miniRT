/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_ray_cone.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:41:25 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/24 16:51:17 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define VO_DOT_AXIS 0
#define D_DOT_AXIS 1

void	intersect_ray_cone(t_inter_vars vars)
{
	intersect_ray_cone_side(&vars);
	intersect_ray_cone_cap(&vars);
}

void	intersect_ray_cone_side(t_inter_vars *vars)
{
	t_co_side	*side;
	t_vec3		vo;
	float		term[2];
	float		coeff[3];
	float		t[2];

	side = &vars->obj->data.cone.side;
	vo = subtract_3dpoints(vars->ray->origin, side->vertex);
	term[VO_DOT_AXIS] = dot(vo, side->axis);
	term[D_DOT_AXIS] = dot(vars->ray->dir, side->axis);
	compute_cone_side_quadratic_coefficients(vars, coeff, vo, term);
	if (solve_quadratic_equation(coeff, t))
	{
		if (is_p_within_cone_height(term[VO_DOT_AXIS], term[D_DOT_AXIS], \
		t[0], side->height))
			update_closest_hit(t[0], SIDE, vars);
		if (t[0] != t[1] && is_p_within_cone_height(term[VO_DOT_AXIS], \
		term[D_DOT_AXIS], t[1], side->height))
			update_closest_hit(t[1], SIDE, vars);
	}
}

void	compute_cone_side_quadratic_coefficients(t_inter_vars *vars, \
float coeff[3], t_vec3 vo, float term[2])
{
	t_co_side	*side;
	t_vec3		v;
	t_vec3		w;
	float		s;

	side = &vars->obj->data.cone.side;
	v = cross(vo, side->axis);
	w = cross(vars->ray->dir, side->axis);
	s = side->height / side->radius;
	coeff[0] = (term[D_DOT_AXIS] * term[D_DOT_AXIS]) - (s * s * dot(w, w));
	coeff[1] = (2 * term[VO_DOT_AXIS] * term[D_DOT_AXIS]) \
				- (2 * s * s * dot(v, w));
	coeff[2] = (term[VO_DOT_AXIS] * term[VO_DOT_AXIS]) \
				- (s * s * dot(v, v));
}

int	is_p_within_cone_height(float vo_dot_axis, float d_dot_axis, float t, \
float cone_height)
{
	if (d_dot_axis > 0)
	{
		if (-vo_dot_axis / d_dot_axis <= t \
		&& t < (cone_height - vo_dot_axis) / d_dot_axis)
			return (1);
	}
	else if (d_dot_axis < 0)
	{
		if (-vo_dot_axis / d_dot_axis >= t \
		&& t > (cone_height - vo_dot_axis) / d_dot_axis)
			return (1);
	}
	else
	{
		if (0 <= vo_dot_axis && vo_dot_axis < cone_height)
			return (1);
	}
	return (0);
}

void	intersect_ray_cone_cap(t_inter_vars *vars)
{
	float		t;

	if (compute_circle_intersection(vars->ray, \
	&vars->obj->data.cone.bottom_cap, &t))
		update_closest_hit(t, BOTTOM_CAP, vars);
}
