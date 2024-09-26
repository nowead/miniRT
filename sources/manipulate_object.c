/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:42:49 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/26 15:52:37 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	key_hook_rotate_object(int keycode, t_vars *vars)
{
	t_obj	*obj;
	t_vec3	*vector;
	float	angle;

	obj = vars->select.curr_obj;
	vector = get_object_orientation_vector(obj);
	if (!vector)
		return ;
	angle = (M_PI * 5.0) / 180.0;
	if (UP_KEY == keycode)
		rotate_vector(vector, (t_vec3){1, 0, 0}, -angle);
	else if (DOWN_KEY == keycode)
		rotate_vector(vector, (t_vec3){1, 0, 0}, angle);
	else if (LEFT_KEY == keycode)
		rotate_vector(vector, (t_vec3){0, 1, 0}, -angle);
	else if (RIGHT_KEY == keycode)
		rotate_vector(vector, (t_vec3){0, 1, 0}, angle);
	else if (LEFT_ANGLE_BRACKET_KEY == keycode)
		rotate_vector(vector, (t_vec3){0, 0, 1}, -angle);
	else if (RIGHT_ANGLE_BRACKET_KEY == keycode)
		rotate_vector(vector, (t_vec3){0, 0, 1}, angle);
	if (obj->type == CYLINDER)
		set_cylinder_cap(&obj->data.cylinder);
	else if (obj->type == CONE)
		set_cone_cap(&obj->data.cone);
}

t_vec3	*get_object_orientation_vector(t_obj *obj)
{
	if (obj->type == SPHERE)
		return (NULL);
	else if (obj->type == PLANE)
		return (&obj->data.plane.normal);
	else if (obj->type == CYLINDER)
		return (&obj->data.cylinder.side.axis);
	else
		return (&obj->data.cone.side.axis);
}

void	key_hook_translate_object(int keycode, t_vars *vars)
{
	t_obj		*obj;
	t_point3	*pos;
	float		distance;

	obj = vars->select.curr_obj;
	pos = get_object_translation_point(obj);
	distance = 0.2;
	if (W_KEY == keycode)
		translate_point(pos, (t_vec3){0, 0, 1}, distance);
	else if (S_KEY == keycode)
		translate_point(pos, (t_vec3){0, 0, -1}, distance);
	else if (A_KEY == keycode)
		translate_point(pos, (t_vec3){-1, 0, 0}, distance);
	else if (D_KEY == keycode)
		translate_point(pos, (t_vec3){1, 0, 0}, distance);
	else if (E_KEY == keycode)
		translate_point(pos, (t_vec3){0, 1, 0}, distance);
	else if (Q_KEY == keycode)
		translate_point(pos, (t_vec3){0, -1, 0}, distance);
	if (obj->type == CYLINDER)
		set_cylinder_cap(&obj->data.cylinder);
	else if (obj->type == CONE)
		set_cone_cap(&obj->data.cone);
}

t_point3	*get_object_translation_point(t_obj *obj)
{
	if (obj->type == SPHERE)
		return (&obj->data.sphere.center);
	else if (obj->type == PLANE)
		return (&obj->data.plane.pos);
	else if (obj->type == CYLINDER)
		return (&obj->data.cylinder.side.center);
	else
		return (&obj->data.cone.side.vertex);
}

void	translate_point(t_point3 *pos, t_vec3 direction, float distance)
{
	t_vec3	move;

	move = scale_vector(direction, distance);
	*pos = add_vector_to_point(*pos, move);
}
