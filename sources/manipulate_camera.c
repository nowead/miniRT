/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_camera.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:59:18 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/25 21:43:16 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define TRANSLATE_FOWARD 0
#define TRANSLATE_BACKWARD 1
#define TRANSLATE_LEFT 2
#define TRANSLATE_RIGHT 3
#define TRANSLATE_UP 4
#define TRANSLATE_DOWN 5

void	key_hook_rotate_camera(int keycode, t_vars *vars)
{
	t_camera	*camera;
	float		angle;

	camera = &vars->scene.camera;
	angle = (M_PI * 5.0) / 180.0;
	if (UP_KEY == keycode)
		rotate_vector(&camera->dir, camera->u, -angle);
	else if (DOWN_KEY == keycode)
		rotate_vector(&camera->dir, camera->u, angle);
	else if (LEFT_KEY == keycode)
		rotate_vector(&camera->dir, (t_vec3){0, 1, 0}, -angle);
	else if (RIGHT_KEY == keycode)
		rotate_vector(&camera->dir, (t_vec3){0, 1, 0}, angle);
}

void	key_hook_translate_camera(int keycode, t_vars *vars)
{
	t_camera	*camera;
	float		distance;

	camera = &vars->scene.camera;
	distance = 0.4;
	if (W_KEY == keycode)
		move_camera(camera, TRANSLATE_FOWARD, distance);
	else if (S_KEY == keycode)
		move_camera(camera, TRANSLATE_BACKWARD, distance);
	else if (A_KEY == keycode)
		move_camera(camera, TRANSLATE_LEFT, distance);
	else if (D_KEY == keycode)
		move_camera(camera, TRANSLATE_RIGHT, distance);
	else if (E_KEY == keycode)
		move_camera(camera, TRANSLATE_UP, distance);
	else if (Q_KEY == keycode)
		move_camera(camera, TRANSLATE_DOWN, distance);
}

void	rotate_vector(t_vec3 *v, t_vec3 axis, float angle)
{
	t_vec3		rotated;
	float		cos_angle;
	float		sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	rotated.x = (cos_angle + (1 - cos_angle) * axis.x * axis.x) * v->x \
				+ ((1 - cos_angle) * axis.x * axis.y - axis.z * sin_angle) \
				* v->y \
				+ ((1 - cos_angle) * axis.x * axis.z + axis.y * sin_angle) \
				* v->z;
	rotated.y = ((1 - cos_angle) * axis.y * axis.x + axis.z * sin_angle) \
				* v->x \
				+ (cos_angle + (1 - cos_angle) * axis.y * axis.y) * v->y \
				+ ((1 - cos_angle) * axis.y * axis.z - axis.x * sin_angle) \
				* v->z;
	rotated.z = ((1 - cos_angle) * axis.z * axis.x - axis.y * sin_angle) \
				* v->x \
				+ ((1 - cos_angle) * axis.z * axis.y + axis.x * sin_angle) \
				* v->y \
				+ (cos_angle + (1 - cos_angle) * axis.z * axis.z) * v->z;
	*v = rotated;
}

void	move_camera(t_camera *camera, int direction, float distance)
{
	t_vec3	move;

	if (direction == TRANSLATE_FOWARD)
		move = scale_vector(camera->dir, distance);
	else if (direction == TRANSLATE_BACKWARD)
		move = scale_vector(camera->dir, -(distance));
	else if (direction == TRANSLATE_LEFT)
		move = scale_vector(camera->u, -(distance));
	else if (direction == TRANSLATE_RIGHT)
		move = scale_vector(camera->u, distance);
	else if (direction == TRANSLATE_UP)
		move = scale_vector(camera->v, distance);
	else
		move = scale_vector(camera->v, -(distance));
	camera->pos = add_vector_to_point(camera->pos, move);
}
