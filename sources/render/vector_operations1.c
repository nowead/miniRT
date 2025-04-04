/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:41:16 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/24 16:55:42 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	subtract_3dpoints(t_point3 p1, t_point3 p2)
{
	return ((t_vec3){p1.x - p2.x, p1.y - p2.y, p1.z - p2.z});
}

float	dot(t_vec3 v1, t_vec3 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vec3	cross(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.y * v2.z - v1.z * v2.y, \
	v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x});
}

t_vec3	scale_vector(t_vec3 v, float s)
{
	return ((t_vec3){v.x * s, v.y * s, v.z * s});
}

t_point3	add_vector_to_point(t_point3 p, t_vec3 v)
{
	return ((t_point3){p.x + v.x, p.y + v.y, p.z + v.z});
}
