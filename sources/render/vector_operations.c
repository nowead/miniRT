/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:41:16 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/08 20:06:38 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3d	subtract_3dpoints(t_point3d p1, t_point3d p2)
{
	return ((t_vector3d){p1.x - p2.x, p1.y - p2.y, p1.z - p2.z});
}

float	dot(t_vector3d v1, t_vector3d v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vector3d	cross(t_vector3d v1, t_vector3d v2)
{
	return ((t_vector3d){v1.y * v2.z - v1.z * v2.y, \
	v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x});
}

t_vector3d	scale_vector(t_vector3d v, float s)
{
	return ((t_vector3d){v.x * s, v.y * s, v.z * s});
}

t_point3d	add_vector_to_point(t_point3d p, t_vector3d v)
{
	return ((t_point3d){p.x + v.x, p.y + v.y, p.z + v.z});
}

float	length(t_vector3d v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector3d	subtract_3dvectors(t_vector3d v1, t_vector3d v2)
{
	return ((t_vector3d){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vector3d	add_3dvectors(t_vector3d v1, t_vector3d v2)
{
	return ((t_vector3d){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

float	cosine_between_vectors(t_vector3d v1, t_vector3d v2)
{
	return (dot(v1, v2) / (length(v1) * length(v2)));
}

t_vector3d	normalize_vector(t_vector3d v)
{
	return (scale_vector(v, 1 / length(v)));
}
