/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_event_hooks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:22:11 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/19 18:28:13 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	// key_hook_rotate(keycode, vars);
	// key_hook_translate(keycode, vars);
	// draw_next_frame(vars);
	return (0);
}

// void	key_hook_rotate(int keycode, t_vars *vars)
// {
// 	if (W_KEY == keycode)
// 		rotate_object(vars, rotate_x, ((M_PI * 5.0) / 180.0));
// 	else if (S_KEY == keycode)
// 		rotate_object(vars, rotate_x, (-(M_PI * 5.0) / 180.0));
// 	else if (A_KEY == keycode)
// 		rotate_object(vars, rotate_y, ((M_PI * 5.0) / 180.0));
// 	else if (D_KEY == keycode)
// 		rotate_object(vars, rotate_y, (-(M_PI * 5.0) / 180.0));
// }

// void	key_hook_translate(int keycode, t_vars *vars)
// {
// 	if (LEFT_KEY == keycode)
// 	{
// 		translate_object(vars, translate_left);
// 		vars->matrix.center.x -= 5;
// 	}
// 	else if (RIGHT_KEY == keycode)
// 	{
// 		translate_object(vars, translate_right);
// 		vars->matrix.center.x += 5;
// 	}
// 	else if (DOWN_KEY == keycode)
// 	{
// 		translate_object(vars, translate_down);
// 		vars->matrix.center.y += 5;
// 	}
// 	else if (UP_KEY == keycode)
// 	{
// 		translate_object(vars, translate_up);
// 		vars->matrix.center.y -= 5;
// 	}
// }
