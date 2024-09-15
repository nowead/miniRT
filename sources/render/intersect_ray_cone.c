/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_ray_cone.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:41:25 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/15 20:40:45 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define	VO_DOT_AXIS 0
#define	D_DOT_AXIS 1

void	intersect_ray_cone(t_inter_vars vars)
{
	compute_cone_side_intersection(&vars);
	// compute_cone_cap_intersection(&vars);
}

void	compute_cone_side_intersection(t_inter_vars *vars)
{
	t_cone	*cone;
	t_vec3	vo;
	float	term[2];
	float	coeff[3];
	float	t[2];

	cone = &vars->obj->data.cone;
	vo = subtract_3dpoints(vars->ray->origin, cone->vertex);
	term[VO_DOT_AXIS] = dot(vo, cone->axis);
	term[D_DOT_AXIS] = dot(vars->ray->dir, cone->axis);
	
	compute_cone_side_quadratic_coefficients(vars, coeff, vo, term);
	if (solve_quadratic_equation(coeff, t))
	{
		if (is_p_within_cone_height(term[VO_DOT_AXIS], term[D_DOT_AXIS], t[0], cone->height))
			update_closest_hit(t[0], SIDE, vars);
		if (t[0] != t[1] && is_p_within_cone_height(term[VO_DOT_AXIS], term[D_DOT_AXIS], t[1], cone->height))
			update_closest_hit(t[1], SIDE, vars);
	}
	return ;
}

void	compute_cone_side_quadratic_coefficients(t_inter_vars *vars, float coeff[3], t_vec3 vo, float term[2])
{
	t_cone	*cone;
	t_vec3	v;
	t_vec3	w;
	float	s;

	cone = &vars->obj->data.cone;
	v = cross(vo, cone->axis);
	w = cross(vars->ray->dir, cone->axis);
	s = cone->height / cone->radius;
	coeff[0] = (term[D_DOT_AXIS] * term[D_DOT_AXIS]) - (s * s * dot(w, w));
	coeff[1] = (2 * term[VO_DOT_AXIS] * term[D_DOT_AXIS]) - (2 * s * s * dot(v, w));
	coeff[2] = (term[VO_DOT_AXIS] * term[VO_DOT_AXIS]) - (s * s * dot(v, v));
}

int	is_p_within_cone_height(float a, float b, float t, float cone_height)
{
	if (b > 0)
	{
		if (-a / b <= t && t < (cone_height - a) / b)
			return (1);
	}
	else if (b < 0)
	{
		if (-a / b >= t && t > (cone_height - a) / b)
			return (1);
	}
	else
	{
		if (0 <= a && a < cone_height)
			return (1);
	}
	return (0);
}
