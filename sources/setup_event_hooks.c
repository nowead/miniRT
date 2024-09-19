/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_event_hooks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:22:11 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/19 21:56:41 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define CLOSE_WINDOW 17
#define PRESS_KEY 2
#define ESC_KEY 53

#define W_KEY 13
#define A_KEY 0
#define S_KEY 1
#define D_KEY 2

#define LEFT_KEY 123
#define RIGHT_KEY 124
#define DOWN_KEY 125
#define UP_KEY 126

#define ROTATE_UP 0
#define ROTATE_DOWN 1
#define ROTATE_LEFT 0
#define ROTATE_RIGHT 1

#define TRANSLATE_FOWARD 0
#define TRANSLATE_BACKWARD 1
#define TRANSLATE_LEFT 0
#define TRANSLATE_RIGHT 1

void	setup_event_hooks(t_vars *vars)
{
	(void)vars;
	mlx_hook(vars->win.ptr, CLOSE_WINDOW, 0, exit_no_error, NULL);
	mlx_hook(vars->win.ptr, PRESS_KEY, 0, key_hook, vars);
}

int	exit_no_error(void)
{
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (ESC_KEY == keycode)
		exit(EXIT_SUCCESS);
	key_hook_rotate_camera(keycode, vars);
	key_hook_translate_camera(keycode, vars);
	draw_next_frame(vars);
	return (0);
}

void	key_hook_rotate_camera(int keycode, t_vars *vars)
{
	if (UP_KEY == keycode)
		rotate_camera_yaw(vars, ROTATE_UP, ((M_PI * 5.0) / 180.0));
	else if (DOWN_KEY == keycode)
		rotate_camera_yaw(vars, ROTATE_DOWN, ((M_PI * 5.0) / 180.0));
	else if (LEFT_KEY == keycode)
		rotate_camera_pitch(vars, ROTATE_LEFT, ((M_PI * 5.0) / 180.0));
	else if (RIGHT_KEY == keycode)
		rotate_camera_pitch(vars, ROTATE_RIGHT, ((M_PI * 5.0) / 180.0));
}

void	key_hook_translate_camera(int keycode, t_vars *vars)
{
	if (W_KEY == keycode)
		move_camera_fb(vars, TRANSLATE_FOWARD, 0.2);
	else if (S_KEY == keycode)
		move_camera_fb(vars, TRANSLATE_BACKWARD, 0.2);
	else if (A_KEY == keycode)
		move_camera_side(vars, TRANSLATE_LEFT, 0.2);
	else if (D_KEY == keycode)
		move_camera_side(vars, TRANSLATE_RIGHT, 0.2);
}

void	draw_next_frame(t_vars *vars)
{
	my_mlx_clear_window(vars);
	render_scene(vars);
	mlx_put_image_to_window(vars->mlx, vars->win.ptr, vars->img.ptr, 0, 0);
}

void	rotate_camera_yaw(t_vars *vars, int rotation, float angle)
{
	t_camera	*camera;

	camera = &vars->scene.camera;
	camera->dir = rotate_vector(&camera->dir, camera->u, angle);
}

// a function that rotate a 3d vector around the given axis
t_vec3	rotate_vector(t_vec3 v, t_vec3 axis, float angle)
{
	t_vec3		rotated;

    // Rodrigues' rotation formula components
    double cosAngle = cos(angle);
    double sinAngle = sin(angle);
	
    rotated.x = (cosAngle + (1 - cosAngle) * axis.x * axis.x) * v.x
             + ((1 - cosAngle) * axis.x * axis.y - axis.z * sinAngle) * v.y
             + ((1 - cosAngle) * axis.x * axis.z + axis.y * sinAngle) * v.z;

    rotated.y = ((1 - cosAngle) * axis.y * axis.x + axis.z * sinAngle) * v.x
             + (cosAngle + (1 - cosAngle) * axis.y * axis.y) * v.y
             + ((1 - cosAngle) * axis.y * axis.z - axis.x * sinAngle) * v.z;

    rotated.z = ((1 - cosAngle) * axis.z * axis.x - axis.y * sinAngle) * v.x
             + ((1 - cosAngle) * axis.z * axis.y + axis.x * sinAngle) * v.y
             + (cosAngle + (1 - cosAngle) * axis.z * axis.z) * v.z;

    return (rotated);
}
