/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_event_hooks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:22:11 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/10 18:36:31 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_event_hooks(t_vars *vars)
{
	(void)vars;
	mlx_hook(vars->win.ptr, CLOSE_WINDOW, 0, exit_no_error, vars);
	mlx_hook(vars->win.ptr, PRESS_KEY, 0, key_hook, vars);
}

int	key_hook(int keycode, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (ESC_KEY == keycode)
	{
		clear_vars(vars);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	exit_no_error(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	clear_vars(vars);
	exit(EXIT_SUCCESS);
}