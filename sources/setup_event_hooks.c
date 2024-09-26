/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_event_hooks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:22:11 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/26 15:33:46 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define CLOSE_WINDOW 17
#define PRESS_KEY 2
#define ESC_KEY 53

#define ONE_KEY 18
#define TWO_KEY 19
#define THREE_KEY 20

void	setup_event_hooks(t_vars *vars)
{
	(void)vars;
	init_select(vars);
	mlx_hook(vars->win.ptr, CLOSE_WINDOW, 0, exit_no_error, NULL);
	mlx_hook(vars->win.ptr, PRESS_KEY, 0, key_hook, vars);
}

void	init_select(t_vars *vars)
{
	t_select_scene_element	*select;
	t_scene					*scene;

	select = &vars->select;
	scene = &vars->scene;
	select->camera = &scene->camera;
	select->obj = scene->obj;
	select->light = scene->lights;
	select->curr_obj = scene->obj;
	select->curr_light = scene->lights;
	select->type = CAMERA;
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
	if (key_hook_select_object(keycode, vars))
	{
		if (vars->select.type == CAMERA)
		{
			key_hook_rotate_camera(keycode, vars);
			key_hook_translate_camera(keycode, vars);
		}
		else if (vars->select.type == OBJECT)
		{
			key_hook_rotate_object(keycode, vars);
			key_hook_translate_object(keycode, vars);
		}
		else
			key_hook_translate_light(keycode, vars);
	}
	draw_next_frame(vars);
	return (0);
}

int	key_hook_select_object(int keycode, t_vars *vars)
{
	t_select_scene_element	*select;

	select = &vars->select;
	if (keycode == ONE_KEY)
		select->type = CAMERA;
	else if (keycode == TWO_KEY)
	{
		select->type = OBJECT;
		if (select->curr_obj->next)
			select->curr_obj = select->curr_obj->next;
		else
			select->curr_obj = select->obj;
	}
	else if (keycode == THREE_KEY)
	{
		select->type = LIGHT;
		if (select->curr_light->next)
			select->curr_light = select->curr_light->next;
		else
			select->curr_light = select->light;
	}
	else
		return (1);
	return (0);
}
