/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_event_hooks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:22:11 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/24 14:01:16 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define CLOSE_WINDOW 17
#define PRESS_KEY 2
#define ESC_KEY 53

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

void	draw_next_frame(t_vars *vars)
{
	my_mlx_clear_window(vars);
	render_scene(vars);
	mlx_put_image_to_window(vars->mlx, vars->win.ptr, vars->img.ptr, 0, 0);
}
