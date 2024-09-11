/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_event_hooks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:22:11 by seonseo           #+#    #+#             */
/*   Updated: 2024/08/31 21:43:05 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_event_hooks(t_vars *vars)
{
	(void)vars;
	mlx_hook(vars->win.ptr, CLOSE_WINDOW, 0, exit_no_error, NULL);
	mlx_hook(vars->win.ptr, PRESS_KEY, 0, key_hook, vars);
}

int	key_hook(int keycode, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (ESC_KEY == keycode)
		exit(EXIT_SUCCESS);
	return (0);
}

int	exit_no_error(void)
{
	exit(EXIT_SUCCESS);
}
